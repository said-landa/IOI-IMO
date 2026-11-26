import random
from datetime import datetime

availableYears = list(range(1989, datetime.now().year + 1))

def randomYear():
    index = random.randrange(len(availableYears))
    return availableYears.pop(index)

for i in range(len(availableYears)):
    print(randomYear())

# 2004
# 2006
# 1996
# 2017
# 2026
# 1993
# 2002
# 2023
# 2018
# 2011
# 1995
# 1999
# 2022
# 2000
# 2025
# 2008
# 1994
# 2021
# 1998
# 2014
# 2015
# 2013
# 2007
# 1989
# 2001
# 2010
# 2020
# 2016
# 2012
# 2019
# 2005
# 1992
# 1997
# 1990
# 2003
# 1991
# 2009
# 2024