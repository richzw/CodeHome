
def permutation(string):
    '''(str) -> list
    
    Get all permutation of element
    >>> permutation('abc')
    ['abc', 'bac', 'bca', 'acb', 'cab', 'cba']
    '''
    if len(string) == 0 or len(string) == 1:
        return string

    result = []
    cur_char = string[0]
    ret_list = permutation(string[1:])
    
    for elem in ret_list:
        for idx in xrange(len(elem)+1):
            new_str = elem[:idx]+cur_char + elem[idx:]
            result.append(new_str)
            
    return result
