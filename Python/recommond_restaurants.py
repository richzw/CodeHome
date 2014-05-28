"""
A restaurant recommendation system.

Here are some example dictionaries.  These correspond to the information in
restaurants_small.txt.

Restaurant name to rating:
# dict of {str: int}
{'Georgie Porgie': 87,
 'Queen St. Cafe': 82,
 'Dumplings R Us': 71,
 'Mexican Grill': 85,
 'Deep Fried Everything': 52}

Price to list of restaurant names:
# dict of {str, list of str}
{'$': ['Queen St. Cafe', 'Dumplings R Us', 'Deep Fried Everything'],
 '$$': ['Mexican Grill'],
 '$$$': ['Georgie Porgie'],
 '$$$$': []}

Cuisine to list of restaurant names:
# dict of {str, list of str}
{'Canadian': ['Georgie Porgie'],
 'Pub Food': ['Georgie Porgie', 'Deep Fried Everything'],
 'Malaysian': ['Queen St. Cafe'],
 'Thai': ['Queen St. Cafe'],
 'Chinese': ['Dumplings R Us'],
 'Mexican': ['Mexican Grill']}

With this data, for a price of '$' and cuisines of ['Chinese', 'Thai'], we
would produce this list:

    [[82, 'Queen St. Cafe'], [71, 'Dumplings R Us']]
"""

# The file containing the restaurant data.
FILENAME = 'restaurants_small.txt'


def recommend(file, price, cuisines_list):
    """(file open for reading, str, list of str) -> list of [int, str] list

    Find restaurants in file that are priced according to price and that are
    tagged with any of the items in cuisines_list.  Return a list of lists of
    the form [rating%, restaurant name], sorted by rating%.
    """

    # Read the file and build the data structures.
    # - a dict of {restaurant name: rating%}
    # - a dict of {price: list of restaurant names}
    # - a dict of {cusine: list of restaurant names}
    name_to_rating, price_to_names, cuisine_to_names = read_restaurants(file)


    # Look for price or cuisines first?
    # Price: look up the list of restaurant names for the requested price.
    names_matching_price = price_to_names[price]

    # Now we have a list of restaurants in the right price range.
    # Need a new list of restaurants that serve one of the cuisines.
    names_final = filter_by_cuisine(names_matching_price, cuisine_to_names, cuisines_list)
    print names_final, name_to_rating

    # Now we have a list of restaurants that are in the right price range and serve the requested cuisine.
    # Need to look at ratings and sort this list.
    result = build_rating_list(name_to_rating, names_final)
    print result

    # We're done!  Return that sorted list.
    return result

def build_rating_list(name_to_rating, names_final):
    """ (dict of {str: int}, list of str) -> list of list of [int, str]

    Return a list of [rating%, restaurant name], sorted by rating%

    >>> name_to_rating = {'Georgie Porgie': 87,
     'Queen St. Cafe': 82,
     'Dumplings R Us': 71,
     'Mexican Grill': 85,
     'Deep Fried Everything': 52}
    >>> names = ['Queen St. Cafe', 'Dumplings R Us']
    [[82, 'Queen St. Cafe'], [71, 'Dumplings R Us']]
    """
    '''
    for key in name_to_rating:
        if key not in names_final:
            del name_to_rating[key]
                
    rating_list = [[v,k] for k,v in name_to_rating.items()]
    ''' 
    # version 1
    rating_list = [[v,k] for k,v in name_to_rating.items() if k in names_final] 
    
    return rating_list
    

def filter_by_cuisine(names_matching_price, cuisine_to_names, cuisines_list):
    """ (list of str, dict of {str: list of str}, list of str) -> list of str

    >>> names = ['Queen St. Cafe', 'Dumplings R Us', 'Deep Fried Everything']
    >>> cuis = 'Canadian': ['Georgie Porgie'],
     'Pub Food': ['Georgie Porgie', 'Deep Fried Everything'],
     'Malaysian': ['Queen St. Cafe'],
     'Thai': ['Queen St. Cafe'],
     'Chinese': ['Dumplings R Us'],
     'Mexican': ['Mexican Grill']}
    >>> cuisines = ['Chinese', 'Thai']
    >>> filter_by_cuisine(names, cuis, cuisines)
    ['Queen St. Cafe', 'Dumplings R Us']
    """
    
    rest_name = []
    
    # v1
    for cuisine in cuisines_list:
        rest_name += list(set(cuisine_to_names[cuisine]) & set(names_matching_price))
    
    # v2
    '''
    for cuisine in cuisines_list:
        for name in cuisine_to_names[cuisine]:
            if name in names_matching_price:
                rest_name.append(name)
    '''
    return rest_name
    

def read_restaurants(file):
    """ (file) -> (dict, dict, dict)

    Return a tuple of three dictionaries based on the information in the file:

    - a dict of {restaurant name: rating%}
    - a dict of {price: list of restaurant names}
    - a dict of {cusine: list of restaurant names}
    """

    name_to_rating = {}
    price_to_names = {'$': [], '$$': [], '$$$': [], '$$$$': []}
    cuisine_to_names = {}
    
    rest_name_arr = []
    rate_arr = []
    cusine_arr = []#[val for key, val in enumerate(lines) if key%5 == 3]
    """
    with open(file) as fd:
        for idx, line in enumerate(fd.readlines()):
            if idx%5 == 0:
                rest_name_arr.append(line.rstrip())
            elif idx%5 == 1:
                rate_arr.append(line.rstrip().strip('%'))
            elif idx%5 == 2:
                price_to_names[line.rstrip()].append(rest_name_arr[idx/5])
            elif idx%5 == 3:
                cusine_arr.append(line.rstrip())
                """
    with open(file) as fd:
    file_contents = fd.readlines()
    file_length = len(file_contents)
    max_index = file_length//5+1 if file_length%5 else file_length//5
    for idx in range(max_index):
        (rest, rate, price, cusine) = file_contents[5*idx:5*idx+4]
        rest_name_arr.append(rest.rstrip())
        rate_arr.append(rate.rstrip().strip('%'))
        price_to_names[price.rstrip()].append(rest_name_arr[idx])
        cusine_arr.append(cusine.rstrip())

    for k, v in zip(cusine_arr, rest_name_arr):
        cuisine_to_names.setdefault(k, []).append(v)

    name_to_rating = dict(zip(rest_name_arr, rate_arr))

    return (name_to_rating, price_to_names, cuisine_to_names)

def main():
    price = '$'
    cuisines_list = ['Chinese', 'Pub Food']
    recommend(FILENAME, price, cuisines_list)

if __name__ == '__main__':
    main()
