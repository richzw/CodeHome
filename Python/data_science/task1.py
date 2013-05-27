import sys
import json

def lines(fp):
    print str(len(fp.readlines()))

def word_dict(fd):
    scores = {}
    for line in fd:
        term, score = line.split('\t')
        scores[term] = int(score)
    return scores

def compute_sentiment(fd, scores):
    results = {}
    line_number = 0;
    for line in fd:
        totle_score = 0
        json_line = json.loads(line)
        if json_line.has_key("text"):
            words = json_line["text"]
            for word in words.split():
                if scores.has_key(word):
                    totle_score += scores[word]
        results[line_number] = totle_score
        line_number += 1
    print results


def main():
    sent_file = open(sys.argv[1])
    tweet_file = open(sys.argv[2])
    compute_sentiment(tweet_file, word_dict(sent_file))

    #lines(sent_file)
    #lines(tweet_file)

if __name__ == '__main__':
    main()
