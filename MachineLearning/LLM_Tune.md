1. 租用Autodl服务器
2. 选择A40服务器租用
镜像
  PyTorch  1.11.0
  Python  3.8(ubuntu20.04)
  Cuda  11.3
GPU   A40(48GB) * 1
CPU   15 vCPU AMD EPYC 7543 32-Core Processor
内存  80GB
硬盘
  系统盘:30 GB
  数据盘:免费:50GB   付费:500GB
  附加磁盘  无
端口映射  无
网络  同一地区实例共享带宽
计费方式  按量计费
费用  ￥2.82/时￥2.82/时

3.  下载01_qwen_qlora.zip文件
cd /root/autodl-tmp
unzip 01_qwen_qlora.zip
cd /root/autodl-tmp/qwen_qlora
vim qwen_download.py

from modelscope.hub.snapshot_download import snapshot_download
model_dir = snapshot_download('qwen/Qwen-14B-Chat', cache_dir='/root/autodl-tmp/jiangxia/base_model/', revision='v1.0.8')

mkdir -p /root/autodl-tmp/jiangxia/base_model/
mkdir -p /root/autodl-tmp/jiangxia/finetune/qwen_qlora/trained_models/Qwen-14B-Chat-Keywords-1118-match-1124/final

apt-get update
apt install net-tools

vim /etc/vim/vimrc

#在文件末尾添加如下内容，处理vim时出现的中文乱码问题
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8

4. 解压后创建虚拟环境modelscope_env，
conda create -n modelscope_env python=3.8.5
pip install modelscope

5. 安装完成后激活modelscope_env
source activate modelscope_env
pip install modelscope

6.  执行qwen模型下载
cd /root/autodl-tmp/qwen_qlora
python qwen_download.py

7. 下载完成，创建虚拟环境 qwen_env（新开一个窗口）
conda create -n qwen_env python=3.8.5

8. 在 qwen_env 中安装requirements.txt
source activate qwen_env
cd /root/autodl-tmp/qwen_qlora
pip install -r requirements.txt

9. 安装完成，在config里面去修改训练参数
cd /root/autodl-tmp/qwen_qlora
vim config/qwen-14b-qlora.json

"model_name_or_path": "/root/autodl-tmp/jiangxia/base_model/Qwen-14B-Chat",
修改为，因为我实际下载解压后的路径就是它：
"model_name_or_path": "/root/autodl-tmp/jiangxia/base_model/qwen/Qwen-14B-Chat",

10. 执行训练
source activate qwen_env
cd /root/autodl-tmp/qwen_qlora
前台执行：
  bash train_qwen_qlora.sh

后台执行：
  nohup bash train_qwen_qlora.sh > 20231203.log 2>&1 &
  
11. 查看显存利用情况
nvidia-smi

12. 持续查看显存变化
watch -n -1 nvidia-smi

13、查看日志
tail -f 20231203.log

14、生成500条比对结果(data/text_matching_data_test_result.csv中有正确答案和预测结果)
source activate qwen_env

cd /root/autodl-tmp/qwen_qlora
#在执行之前先修改如下内容，一是路径，二是os包问题
vim evaluation/model_evaluation.py

import sys
import os
curPath = os.path.abspath(os.path.dirname(__file__))
rootPath = os.path.split(curPath)[0]
sys.path.insert(0, os.path.split(rootPath)[0])
sys.path.append("../")
from component.utils import ModelUtils

model_name_or_path = '/root/autodl-tmp/jiangxia/base_model/qwen/Qwen-14B-Chat'
adapter_name_or_path = '/root/autodl-tmp/qwen_qlora/trained_models/Qwen-14B-Chat-Keywords-1118-match-1124/final'

with open('/root/autodl-tmp/qwen_qlora/data/text_matching_data_test.jsonl',
                'r', encoding='utf-8') as read_file, \
          open('/root/autodl-tmp/qwen_qlora/data/text_matching_data_test_result.csv',
                'w+', encoding='utf-8') as write_file:



执行
cd /root/autodl-tmp/qwen_qlora/evaluation
python model_evaluation.py


注意事项：
1、训练任务时注意观察Task数，一般Task数量在1000以上才会产生一个比较好的效果，对于几万条以上数据的情况。
2、下载Chat版本的qwen14B，因为Chat版本经过了大量的指令微调，效果会更好。
3、单卡训练的话直接bash脚本即可，同时如果时间较长，使用后台运行的方式运行脚本，然后将ssh退掉，重新开一个ssh连接，再去看日志。
4、lora_rank是把全连接层做一个int4的量化，AB矩阵中的r值，这样参数量就是d X r + r X k，相比于未量化之前的d X k，能节省较多的资源。
  同时r越大，在lora中可训练的数据量也就越大，在越垂的场景，r值要尽可能的大，这样才能训练更多的数据，改变原始模型的参数分布，
  这样lora的整体效果才会更好，lora_rank值64起步。
5、d X r + r X k计算出结果后，在附加到原始的d X k中，作为一个总体的输出。在附加之前，d X r + r X k需要乘以一个 α/系数，lora_alpha的值
  就是表示这样一个比例，这个比例至决定了d X r + r X k 是以放大还是缩小的形式附加到原始的d X k上。
6、output_dir是qlora训练完成之后的结果文件保存路径
7、module_name_or_path是qwen14B Chat下载之后保存的路径
8、train_file是我们要训练的数据文件
9、num_train_epochs是epochs的数量
10、pre_device_train_batch_size表示每个GPU的Batch Size，如果有2个GPU，则总的Batch Size就是pre_device_train_batch_size乘以2
11、gradient_accumulation_step是就是保存前几个step阶段的前向传播的结果，然后计算平均值进行反向传播，可以节省计算资源，可以将其看做是
  Batch Size的一部分，也就是总的Batch Size是 (pre_device_train_batch_size X GPU个数 X gradient_accumulation_step)
12、learning_rate是学习率，在训练过程中可以调整不同的学习率来观察损失的情况
13、max_seq_length是输入长度
14、logging表示每隔多少个Step打印一次损失信息
15、save_step表示每隔多少步去保存
16、save_total_limit表示一共要保存多少个版本，如果是全参数微调，一个checkpoint就大几十G的显存，因此此值一般设置为1
17、warmup_steps在参数微调阶段非常重要，表示将warmup_steps个步长去逐步增加到某个学习率值
18、gradient_checkpointing表示是否启动，如果启动，就不保存中间结果值，以时间换空间，节省显存空间
19、seed随机因子，保证训练结果可复现
20、dataloder_num_worker是否多进程加载数据
21、save_strategy存储策略，一般设置为steps，在训练时，不要一下子上来就把显存给占满，因为在训练过程中，torch会产生很多碎片，会导致OOM
22、主要调节的参数是num_train_epochs、pre_device_train_batch_size、gradient_accumulation_step、learning_rate、warmup_steps
23、修改utils/merge_lora.py中的module_name_or_path为千问，主要是将原始模型与之前训练的模型进行合并
24、lora_dropout一般设置为0.5，主要是防止过拟合
25、修改config目录下的qwen-14b-qlora.json，将module_name_or_path修改为自己下载好的千问模型路径
26、如果是单卡，train_qwen_qlora.sh文件中的CUDA_VISIBLE_DEVICES设置为0即可




1. 租用 Autodl/恒源云/智星云 服务器   

2. 选择 A100 80G/A800 80G 务器租用（2卡或以上），使用pytorch 1.11.0  python3.8版本镜像

3. 下载02_llm_code.zip
cd /root/autodl-tmp
unzip 02_llm_code.zip
cd /root/autodl-tmp/llm_code
vim llm_download/baichuan2_7B_base_download.py

from modelscope.hub.snapshot_download import snapshot_download
model_dir = snapshot_download('baichuan-inc/Baichuan2-7B-Chat', cache_dir='/root/autodl-tmp/jiangxia/base_model/', revision='v1.0.2')

mkdir -p /root/autodl-tmp/jiangxia/base_model/

apt-get update
apt install net-tools

vim /etc/vim/vimrc

#在文件末尾添加如下内容，处理vim时出现的中文乱码问题
set fileencodings=utf-8,ucs-bom,gb18030,gbk,gb2312,cp936
set termencoding=utf-8
set encoding=utf-8

4. 解压后创建虚拟环境modelscope_env
conda create -n modelscope_env python=3.8.5
pip install modelscope

5. 安装完成后激活modelscope_env
source activate modelscope_env
pip install modelscope
cd /root/autodl-tmp/llm_code
pip install -r requirements.txt

6.  执行模型下载
cd /root/autodl-tmp/llm_code
python llm_download/baichuan2_7B_base_download.py

7. 下载完成，创建虚拟环境 llm_env（新开一个窗口）
conda create -n llm_env python=3.8.5

8. 在 llm_env 中安装requirements.txt
source activate llm_env
cd /root/autodl-tmp/llm_code
pip install -r requirements.txt

9. 安装完成，在training_config/baichuan2_config.json 里面去修改训练参数（例如模型路径）
cd /root/autodl-tmp/llm_code
vim training_config/baichuan2_config.json

"model_name_or_path": "/root/autodl-tmp/jiangxia/base_model/baichuan-inc/Baichuan2-7B-Chat",
"deepspeed": "/root/autodl-tmp/llm_code/deepspeed_config/deepspeed_stage_1_config.json",
"train_file": "/root/autodl-tmp/llm_code/data/psychology_data.jsonl",

10. 根据租用的GPU数量修改train_ft.sh里面的GPU配置
cd /root/autodl-tmp/llm_code
vim train_ft.sh

CUDA_VISIBLE_DEVICES=0,1 deepspeed --num_gpus=2 --master_port 65224 train.py --train_args_file /root/autodl-tmp/llm_code/training_config/baichuan2_config.json

11. 执行训练
cd /root/autodl-tmp/llm_code
前台执行：
  bash train_ft.sh

后台执行：
  nohup bash train_ft.sh > 20231203.log 2>&1 &

11. 查看显存利用情况
nvidia-smi

12. 持续查看显存变化
watch -n -1 nvidia-smi

13、查看文件大小
ls -alh

14、训练完成之后将final中的没有的文件从Baichuan中拷贝过来

15、在common/constants.py中，需要将LLM_MODULE_MODEL_PATH改为训练完成的模型路径
cd /root/autodl-tmp/llm_code
vim common/constants.py

LLM_MODULE_MODEL_PATH = '/root/autodl-tmp/jiangxia/base_model/baichuan-inc/Baichuan2-7B-Chat'

17、启动demo
source activate modelscope_env
cd /root/autodl-tmp/llm_code/llm_demo
vim baichuan2_demo.py

model_dir = "/root/autodl-tmp/jiangxia/base_model/baichuan-inc/Baichuan2-7B-Chat"

python baichuan2_demo.py

18、启动Service
source activate modelscope_env
cd /root/autodl-tmp/llm_code/service
bash server.sh

19、启动客户端
source activate modelscope_env
cd /root/autodl-tmp/llm_code/service
python client.py

19、启动前端页面
端口是17860，映射端口语句为（windows + R cmd窗口中执行）：
ssh -CNg -L 17860:127.0.0.1:17860 root@connect.neimeng.seetacloud.com -p 23648
  
source activate modelscope_env
cd /root/autodl-tmp/llm_code/web_framework
bash web_service.sh

20、执行mmcu脚本
source activate modelscope_env
cd /root/autodl-tmp/llm_code/llm_evaluation
vim mmcu.sh

base_model_path="/root/autodl-tmp/jiangxia/base_model/baichuan-inc/Baichuan2-7B-Chat"

bash mmcu.sh

结果文件保存在：/root/autodl-tmp/llm_code/llm_evaluation/result/mmcu

21、执行bleu脚本
source activate modelscope_env
cd /root/autodl-tmp/llm_code/llm_evaluation

bash bleu.sh

结果文件保存在：/root/autodl-tmp/llm_code/llm_evaluation/result/bleu/psychology_result_bleu.txt


注意事项：
1、当直接加载Bash版本时，往往大模型会答非所问。在经过几万条高质量数据的SFT之后，会取得一个较好的效果。这7万条多条数据是从ChatGPT中爬取得来的，
  或者从书籍中截取，然后让ChatGPT生成答案得来的。
2、deepspeed_config目录下有三个stage版本的配置文件，如果是7B Base版大模型，4卡的A100，可以使用stage1。如果是2卡的A100，可以使用
  stage3。大概在时间上相差两倍以上。另外，使用stage3时，offload配置会导致训练时间变慢2到3倍。两卡的A100 80G只能使用Stage3跑，不然会崩，
  大概需要20个小时（开启了offload）,如果关闭了offload，需要14个小时。
3、llm_demo目录下主要是在本地启动一个示例来体验大模型微调的一个效果
4、llm_download目录主要是用来下载百川7B模型的
5、llm_evaluation目录下是用来进行模型评估的，主要是垂域问题的评估、bashMak的评估
6、module_interface目录一方面我们在界面中会调用模型的predict方法，另一方面会在提供外部服务的时候提供生成方法，主要实现了大模型的生成逻辑。
  在Service和Web端会调用ganera的生成接口。
7、service目录是使用Starlette启动服务，Starlette在处理并行数据的能力较强
8、training_config目录是百川全参数微调的训练参数配置，pre_device_train_batch_size值没有设置16的原因是在训练后期会崩，我们可以设置为8，目前是12，
  learning_rate设置为1e-5是一个偏保守的时，我们在训练过程中可以设置大一些。但是如果选得过高的话，会导致一定程度的灾难性遗忘。
9、web_framework目录是用来部署前端页面的
10、在租用服务器时至少选用两张A800或者两张A100的80G，不然训练时间会很长。老师使用的是两张A100的80G
11、output_dir是qlora训练完成之后的结果文件保存路径
12、model_name_or_path是我们要进行训练的模型位置
13、deepspeed_config配置文件路径
14、train_file是训练数据的地址
15、num_train_epochs是epochs的数量，在进行全参数微调时取1就可以了，最多不超过2个，不然会出现灾难性遗忘，导致训练效果不好。
16、pre_device_train_batch_size是每个GPU的Batch Size
17、gradient_accumulation_step是每个step的梯度累计
18、save_step可以设置得密一些，save_step表示每隔多少步去保存checkpoint，如果设置得太大，比如设置1000步，如果在999步崩了，那么就亏大了。
19、save_total_limit必须设置为1，save_total_limit表示一共要保存多少个版本，如果是全参数微调，一个checkpoint就大几十G的显存，因此设置为1
20、gradient_accumulation_step是否使用梯度累计
21、gradient_clipping是否做梯度裁剪，防止梯度爆炸
22、steps_per_print打印间隔
22、train_batch_size使用的batch、train_micro_batch_size_per_gpu每个GPU使用的batch
23、wall_clock_breakdowm是否打印相关信息
24、loss_scale动态损失的扩大。initial_scale_power扩大的比例，initial_scale_power=16，则扩大的比例就是2的16次方。hysteresis延迟的时间，
  min_loss_scale最小的scale比例
25、contiguous_gradients是否使用连续的方式存储梯度
26、bleu.py，我们在使用bleu时，主要是使用了nltk中的bleu_soore包，按照ngrams1/2/3/4分别计算目标文本和生成文本之间的重合度，计算它们之间的
  bleu值，需要使用到sentence_bleu函数。weights=[0.25, 0.25, 0.25, 0.25]表示对应ngrams1/2/3/4以四分之一的比例去做加权组合。
27、epochs设置为1，pre_device_train_batch_size设置为4，gradient_accumulation_step设置为4
28、在train_ft.sh中，如果是两卡，CUDA_VISIBLE_DEVICES=0,1  num_gpus=2，然后train_args_file填写实际的配置文件路径即可
