# coding=utf-8

from sys import argv
import sys
import random
from random import randrange

num_tuples, filename = int(sys.argv[1]), sys.argv[2]
days = ['Monday','Tuesday','Wednesday','Thursday','Friday','Saturday','Sunday']
people = ['Rene,German,1,35', 'Eric,Linstead,5,55', 'Lance,Fluger,2,40']
drinkType = ['Brunch', 'Cocktail', 'Classic', 'Tropical', 'College', 'Gentleman\'s', 'Lady\'s']
glassType = ['High Ball','Flute', 'Mug', 'Martini', 'Wine', 'Snifter', 'Shot']
nameTypeOne = ['Old Fashioned', 'Martini', 'Manhattan','Daiquiri', 'Margarita','Bloody Mary', 'Coffee','Fizz','Julep', 'Mai Tai', 'Sour','Cosmo', 'Tom Collins', 'Bubbler', 'FUBAR', 'Juice', 'Momma','Daddy','Donkey','Panda','Dolphin','Flame','Valentine','Berzerker','German', 'Fluger', 'Linstead', 'Sasquatch','Chapman']
nameTypeTwo = ['Mint', 'Sour', 'Red', 'Yellow', 'Green', 'Blue', 'Deadly', 'Fizzy', 'Hairy', 'French', 'Irish', 'Italian', 'Bloody', 'Sweet', 'Short', 'Tall', 'Extra Dry', 'Spicy','Flaming', 'Rene\'s', 'Lance\'s', 'Eric\'s','Kanye', 'Stirred', 'Shaken', 'Upside-down']
ingredient_options = ['Rum', 'Vodka', 'Tequila', 'Gin', 'Bourbon', 'Whiskey', 'Triple Sec', 'Vermouth', 'Lemonade', 'Orange juice', 'Apple juice', 'Soda Water', 'Coke', 'Baileys', 'Grand Marnier', 'Simple Syrup', 'Cranberry Juice', 'Sweet and Sour', 'Tobasco sauce', 'Red bull', 'Coffee','Grenadine', 'Crème de Menthe', 'St. Germain', 'Tomato Juice', 'Pineapple Juice', 'Grapefruit Juice', 'Bitters', 'Ginger Ale', 'Salt', 'Sugar Cube', 'Coconut Shreds', 'Mint', 'Lemon peel', 'Orange peel', 'Cherry', 'Olive', 'Olive juice', 'Heavy Cream']

CSV_file = open(filename, 'w')
numOfIngredients = 2

def gen_numOfIngredients():
    return randrange(2,5)

def gen_ingredients():
    numOfIngredients = gen_numOfIngredients()
    ingredients = str(numOfIngredients) + ','
    while(numOfIngredients):
        if numOfIngredients == 1:
            ingredients += random.choice(ingredient_options)
        else:
            ingredients += random.choice(ingredient_options) + ','
        numOfIngredients -= 1
    return ingredients

def gen_name():
    drink_name = random.choice(nameTypeOne)
    int_nameDescr = randrange(0, 9)
    if(int_nameDescr > 2):
        drink_name = random.choice(nameTypeTwo) + ' ' + drink_name
    return drink_name

def gen_tuple():
    newTuple = gen_name()
    newTuple += ',' + gen_ingredients()
    newTuple += ',' + random.choice(drinkType)
    newTuple += ',' + random.choice(glassType)
    newTuple += ',' + str(randrange(4,14))
    newTuple += ',' + random.choice(days)
    newTuple += ',' + random.choice(people)
    return newTuple

while(num_tuples):
    CSV_file.write(gen_tuple())
    CSV_file.write("\n")
    num_tuples -= 1

CSV_file.close()


#Drink name (1), num ingredients(2), ingredients (3),
#type (4), glass (5), cost (6), popular day ordered (7),
#who prefers (8), their bar visits per week (9), their hours worked per week (10)
