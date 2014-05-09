#Q. Write a function to reverse each word in a string.
def reverse_each_word(words):
    '''
    Reverse each word in a string 
    '''
    return " ".join([x[::-1] for x in words.split(' ')])
    

#Q. Given two arrays find which elements are not in the second.
def find_not_in_second(first, second): 
    '''
    Find which numbers are not in the
    second array
    '''
    return [x for x in first if x not in second]

