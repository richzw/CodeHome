// Q: 有两个纯文本文件，其中一个较大，大约上万行，每行是一个具体的域名，比如wudaokou.haidian.beijing.com。
//    另外一个较小，大约一千多行，每行是一个大域名，比如beijing.com。现在想找到一个较快的算法，
//    迅速判断小文件中的大域名清单是否能涵盖大文件中的所有域名。 

A:  追求算法效率可用trie，域名倒序，然后砍节点。追求编码简单就先reverse域名再排序，然后用binary search删区间.

bool covered(const vector<string>& filters, const string& line){
  typedef vector<string>::const_iterator Iterator;
  Iterator filter = lower_bound(filters.begin(), filters.end(), line);
  if (filter != filters.end() && *filter == line)
    return true;
  if (filter != filters.begin())
  {
    --filter;
    if (line.size() >= filter->size()
        && equal(filter->begin(), filter->end(), line.begin()))
      return true;
  }
  return false;
}

int main(int argc, char* argv[])
{
  if (argc == 3)
  {
    vector<string> filters;
    {
      ifstream in2(argv[2]);
      string filter;
      while (getline(in2, filter))
      {
        reverse(filter.begin(), filter.end());
        if (filter[filter.size()-1] != '.')
          filter.push_back('.');

        filters.push_back(filter);
      }
    }
    sort(filters.begin(), filters.end());

    {
      ifstream in1(argv[1]);
      string line;
      while (getline(in1, line))
      {
        reverse(line.begin(), line.end());
        if (line[line.size()-1] != '.')
          line.push_back('.');
        
        if (!covered(filters, line))
        {
          cout << "remain " << line << '\n';
        }
      }
    }
  }
}
