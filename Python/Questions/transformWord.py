'''
Given a source word, target word and an English dictionary,
transform the source word to target by changing/adding/removing 1 character at a time, while all intermediate words
being valid English words. Return the transformation chain which has the smallest number of intermediate words.
'''
def constructGraph(dictionary):
    graph = collections.defaultdict(list)
    letters = string.lowercase
    
    for word in dictionary:
        for idx in xrange(len(word)):
            # remove one letter
            remove = word[:idx]+word[idx+1:]
            if remove in dictionary:
                graph[word].append(remove)
            # change one letter
            for letter in letters:
                change = word[:idx]+letter+word[idx+1:]
                if change in dictionary:
                    graph[word].append(change)
        # add one letter
        for letter in letters:
            for idx in xrange(len(word)+1):
                add = word[:idx]+letter+word[idx:]
                if add in dictionary:
                    graph[word].append(add)
    return graph

def transformWord(graph, origin, goal):
    paths = collections.deque([[origin]])
    wordMap = set()
    # Breadth First Search
    while len(paths) != 0:
        curPath = paths.popleft()
        curWord = curPath[-1]
        if curWord == goal:
            return curPath
        elif curWord in wordMap:
            continue
        
        wordMap.append(curWord)
        transforms = graph[curWord]
        for word in transforms:
            if word not in curPath:
                # avoid loops
                paths.append(curPath[:]+[word])

    return []
