#
#  Author: Ayesha Quadri Syeda
#  Purpose: Implement the presentation-tier
#  Due Date: 10/7/2022
#

###########################################################
import sqlite3
import objecttier


###########################################################
#  command 1
#  Asks for a movie name and returns all the movies
#  with that name in the database
#
def command_one(dbConn):
  
  print()
  name = input("Enter movie name (wildcards _ and % supported): ")
  print()

  list = objecttier.get_movies(dbConn, name)
  
  print("# of movies found: ", len(list))
  print()
  
  ## If too many movies are found
  if len(list) > 100:
    print("There are too many movies to display, please narrow your search and try again...")
    print()
    return 

  ##  If None is returned
  if list == None:
    return

  #  Print the info
  for row in list:
    print(row.Movie_ID, ":", row.Title, "({})".format(row.Release_Year))

  print() 
##########################################################
#  command 2
#  Asks for a Movie ID and returns all the details
#  stored in the database about that movie
#
def command_two(dbConn):
  print()
  id = input("Enter movie id: ")
  print()
  
  movie = objecttier.get_movie_details(dbConn, id)

  #  If None is returned
  if movie == None:
    print("No such movie...")
    print()
    return

  #  Print all the information
  print(movie.Movie_ID, ":", movie.Title)
  print("  Release date:", movie.Release_Date)
  print("  Runtime:", movie.Runtime, "(mins)")
  print("  Orig language:", movie.Original_Language)
  print("  Budget:", f"${movie.Budget:,} (USD)")
  print("  Revenue:", f"${movie.Revenue:,} (USD)")
  print("  Num reviews:", movie.Num_Reviews)
  print("  Avg rating: ", f"{movie.Avg_Rating:.2f}", "(0..10)")

  #  Print the list of Genres
  print("  Genres:", end=" ")
  for genre in movie.Genres:
    print( f"{genre:},", end=" ")
  print()

  #  Print the list of Production Companies
  print("  Production companies:", end=" ")
  for comp in movie.Production_Companies:
    print( f"{comp:},", end=" ")
  print()
  print("  Tagline:", movie.Tagline)
  print()

########################################################
#  command 3
#  Asks for the top N and minimum reviews 
#  returns the top N movies that have at least the minimum 
#  reviews
#
def command_three(dbConn):

  print()
  n = int(input("N? "))

  #  validate N value
  if n <= 0:
    print("Please enter a positive value for N...")
    print()
    return

  #  validate min # of reviews
  min = int(input("min number of reviews? "))
  if min <= 0:
    print("Please enter a positive value for min number of reviews...")
    print()
    return
  print()

  list = objecttier.get_top_N_movies(dbConn, n, min)
  if len(list) == 0 or list == -1:
    return

  #  Print the information
  for l in list:
    print(l.Movie_ID, ":", l.Title, 
          "({}),".format(l.Release_Year), "avg rating =",
          f"{l.Avg_Rating:.2f}", 
          "({} reviews)".format(l.Num_Reviews))
  print()
  
##########################################################
#  command 4
#  Asks for a rating and Movie ID
#  Returns a message if the review was inserted
#  Returns a message if no movie with the Movie ID was 
#  found
#
def command_four(dbConn):
  print()
  rating = int(input("Enter rating (0..10): "))

  #  Validate the rating
  if rating < 0 or rating > 10:
    print("Invalid rating...")
    print()
    return
  id = int(input("Enter movie id: "))
  print()

  num = objecttier.add_review(dbConn, id, rating)

  #  Check if the insert was successful
  if num == 1:
    print("Review successfully inserted")
    print()
  else:
    print("No such movie...")
    print()
    return
    
##########################################################
#  command 5
#  Asks for the new tagline 
#  Replaces the old tagline with the new one
#
def command_five(dbConn):
  print()
  line = input("tagline? ")
  id = int(input("movie id? "))
  print()
  
  num = objecttier.set_tagline(dbConn, id, line)

  if num == 1:
    print("Tagline successfully set")
    print()
  else:
    print("No such movie...")
    print()
    return
  
##########################################################
##  main
##########################################################
  
dbConn = sqlite3.connect('MovieLens.db')

#  Default Stats
print("** Welcome to the MovieLens app **")
print()
print("General stats:")
print("  # of movies:", 
      f"{objecttier.num_movies(dbConn):,}")
print("  # of reviews:", 
      f"{objecttier.num_reviews(dbConn):,}")

print()

#  Commands
val = input("Please enter a command (1-5, x to exit): ")

while val != 'x':
  if val == '1':
    command_one(dbConn)
  elif val == '2':
    command_two(dbConn)
  elif val == '3':
    command_three(dbConn)
  elif val == '4':
    command_four(dbConn)
  elif val == '5':
    command_five(dbConn)
  else:
    print('**Error, unknown command, try again...')
    print()
    
  val = input('Please enter a command (1-5, x to exit): ')
