# Ayesha Quadri Syeda
# Implement the Object-tier of the project
# 10/4/2022
############################################################
# File: objecttier.py
#
# Builds Movie-related objects from data retrieved through 
# the data tier.
#
# Original author:
#   Prof. Joe Hummel
#   U. of Illinois, Chicago
#   CS 341, Spring 2022
#   Project #02
#
import datatier


##################################################################
#
# Movie:
#
# Constructor(...)
# Properties:
#   Movie_ID: int
#   Title: string
#   Release_Year: string
#
class Movie:
  def __init__(self, movie_id, title, release_year):
    self._Movie_ID = movie_id
    self._Title = title
    self._Release_Year = release_year

  @property
  def Movie_ID(self):
    return self._Movie_ID
     
  @property
  def Title(self):
    return self._Title
     
  @property
  def Release_Year(self):
    return self._Release_Year
  


##################################################################
#
# MovieRating:
#
# Constructor(...)
# Properties:
#   Movie_ID: int
#   Title: string
#   Release_Year: string
#   Num_Reviews: int
#   Avg_Rating: float
#
class MovieRating:
  def __init__(self, movie_id, title, release_year, num_reviews, avg_rating):
    self._Movie_ID = movie_id
    self._Title = title
    self._Release_Year = release_year
    self._Num_Reviews = num_reviews
    self._Avg_Rating = avg_rating

  @property
  def Movie_ID(self):
    return self._Movie_ID

  @property
  def Title(self):
    return self._Title

  @property
  def Release_Year(self):
    return self._Release_Year

  @property
  def Num_Reviews(self):
    return self._Num_Reviews

  @property
  def Avg_Rating(self):
    return self._Avg_Rating


##################################################################
#
# MovieDetails:
#
# Constructor(...)
# Properties:
#   Movie_ID: int
#   Title: string
#   Release_Date: string, date only (no time)
#   Runtime: int (minutes)
#   Original_Language: string
#   Budget: int (USD)
#   Revenue: int (USD)
#   Num_Reviews: int
#   Avg_Rating: float
#   Tagline: string
#   Genres: list of string
#   Production_Companies: list of string
#
class MovieDetails:
  def __init__(self, movie_id, title, release_date, runtime, original_language, budget, revenue, num_reviews, avg_rating, tagline, genres = [], production_companies = []):
    
    self._Movie_ID = movie_id
    self._Title = title
    self._Release_Date = release_date
    self._Runtime = runtime
    self._Original_Language = original_language
    self._Budget = budget
    self._Revenue = revenue
    self._Num_Reviews = num_reviews
    self._Avg_Rating = avg_rating
    self._Tagline = tagline
    self._Genres = genres
    self._Production_Companies = production_companies

  @property
  def Movie_ID(self):
    return self._Movie_ID

  @property
  def Title(self):
    return self._Title

  @property
  def Release_Date(self):
    return self._Release_Date

  @property
  def Runtime(self):
    return self._Runtime

  @property
  def Original_Language(self):
    return self._Original_Language

  @property
  def Budget(self):
    return self._Budget

  @property
  def Revenue(self):
    return self._Revenue
    
  @property
  def Num_Reviews(self):
    return self._Num_Reviews

  @property
  def Avg_Rating(self):
    return self._Avg_Rating

  @property
  def Tagline(self):
    return self._Tagline

  @property
  def Genres(self):
    return self._Genres

  @property
  def Production_Companies(self):
    return self._Production_Companies


##################################################################
# 
# num_movies:
#
# Returns: # of movies in the database; if an error returns -1
#
def num_movies(dbConn):

  sql = "Select count(Movie_ID) From Movies;"

  count = datatier.select_one_row(dbConn, sql)

  if count == None:
    return -1

  return count[0]


##################################################################
# 
# num_reviews:
#
# Returns: # of reviews in the database; if an error returns -1
#
def num_reviews(dbConn):
  sql = "Select count(Rating) From Ratings;"

  count = datatier.select_one_row(dbConn, sql)

  if count == None:
    return -1

  return count[0]


##################################################################
#
# get_movies:
#
# gets and returns all movies whose name are "like"
# the pattern. Patterns are based on SQL, which allow
# the _ and % wildcards. Pass "%" to get all stations.
#
# Returns: list of movies in ascending order by name; 
#          an empty list means the query did not retrieve
#          any data (or an internal error occurred, in
#          which case an error msg is already output).
#
def get_movies(dbConn, pattern):
  sql = """Select Movie_ID, Title, 
           strftime('%Y', Release_Date)
           From Movies
           where Title like ?
           Order by Title;"""

  rows = datatier.select_n_rows(dbConn, sql, [pattern])

  #  Check for empty list
  if(rows == None):
    return -1

  #  Create a list of Movie object 
  list = []
  for row in rows:
    m = Movie(row[0], row[1], row[2])
    list.append(m)

  return list


##################################################################
#
# get_movie_details:
#
# gets and returns details about the given movie; you pass
# the movie id, function returns a MovieDetails object. Returns
# None if no movie was found with this id.
#
# Returns: if the search was successful, a MovieDetails obj
#          is returned. If the search did not find a matching
#          movie, None is returned; note that None is also 
#          returned if an internal error occurred (in which
#          case an error msg is already output).
#
def get_movie_details(dbConn, movie_id):
  #  Gets info from Movies table
  # sql1 = """Select Movie_ID, Title, 
  #           strftime('%Y-%m-%d'), Runtime, Original_Language,
  #           Budget, Revenue
  #           From Movies
  #           where Movie_ID = ?"""

  sql = """Select Movies.Movie_ID, Movies.Title, strftime('%Y-%m-%d', Release_Date), 
           Movies.Runtime, Movies.Original_Language, Movies.Budget,
           Movies.Revenue, Movie_Taglines.Tagline 
           From Movies
           Join Movie_Taglines
           on Movies.Movie_ID = Movie_Taglines.Movie_ID
           where Movies.Movie_ID = ?;"""
  
  row1 = datatier.select_one_row(dbConn, sql, [movie_id])

  if row1 == None or len(row1) == 0:
    return None

  #  Gets info from Ratings table
  sql2 = """Select count(*), avg(Rating) From Ratings
            where Movie_ID = ?"""

  row2 = datatier.select_one_row(dbConn, sql2, [movie_id])

  if row2 == None or len(row2) == 0:
    return None

  # average = round((row2[1]/row2[0]), 2)

  # #  Gets info from Movie_Taglines table
  # # sql3 = """Select Tagline from Movie_Taglines 
  # #            where Movie_ID = ? """

  # # row3 = datatier.select_one_row(dbConn, sql3, [movie_id])

  # #  Gets Genre info
  sql4 = """Select Genre_Name from Genres
            join Movie_Genres 
            on Genres.Genre_ID = Movie_Genres.Genre_ID
            where Movie_Genres.Movie_ID = ?
            group by Genres.Genre_ID;"""

  rows1 = datatier.select_n_rows(dbConn, sql4, [movie_id])

  if rows1 == None or len(rows1) == 0:
    return None

  #  same data in an array
  genres = []
  for row in rows1:
    genres.append(row[0])

  #  Gets Production companies
  sql5 = """Select Company_Name From Companies
            join Movie_Production_Companies
            on Companies.Company_ID = Movie_Production_Companies.Company_ID
            where Movie_Production_Companies.Movie_ID = ?;"""

  rows2 = datatier.select_n_rows(dbConn, sql5, [movie_id])

  if rows2 == None or len(rows2) == 0:
    return None

  companies = []
  for row in rows2:
    companies.append(row[0])

  # md = MovieDetails(row1[0], row1[1], row1[2], row1[3], row1[4], row1[5], row1[6], row2[0], row2[1], row3[0], genres, companies)
  
  # print(row1[0])
  # print(row1[1])
  # print(row1[2])
  # print(row1[3])
  # print(row1[4])
  # print(row1[5])
  # print(row1[6])
  # print(row1[7])

  if row2[1] == None:
    md = MovieDetails(row1[0], row1[1], row1[2], row1[3], row1[4], row1[5], row1[6], row2[0], 0, row1[7], genres, companies)
  
  md = MovieDetails(row1[0], row1[1], row1[2], row1[3], row1[4], row1[5], row1[6], row2[0], row2[1], row1[7], genres, companies)
  

  return md

##################################################################
#
# get_top_N_movies:
#
# gets and returns the top N movies based on their average 
# rating, where each movie has at least the specified # of
# reviews. Example: pass (10, 100) to get the top 10 movies
# with at least 100 reviews.
#
# Returns: returns a list of 0 or more MovieRating objects;
#          the list could be empty if the min # of reviews
#          is too high. An empty list is also returned if
#          an internal error occurs (in which case an error 
#          msg is already output).
#
def get_top_N_movies(dbConn, N, min_num_reviews):
  sql = """Select Movies.Movie_ID, Title, 
           strftime('%Y', Release_Date) as year, 
           avg(Rating) as review, count(Rating) as num
           from Ratings
           Join Movies
           on Ratings.Movie_ID = Movies.Movie_ID
           group by Movies.Movie_ID
           Having num >= ?
           order by review desc
           limit ?;"""

  rows = datatier.select_n_rows(dbConn, sql, [min_num_reviews, N])

  # if len(rows) == 0:
  #   print("Here")
  if rows == None:
    return -1
    
  list = []

  for row in rows:
    mr = MovieRating(row[0], row[1], row[2], row[4], row[3])
    list.append(mr)

  return list
  

##################################################################
#
# add_review:
#
# Inserts the given review --- a rating value 0..10 --- into
# the database for the given movie. It is considered an error
# if the movie does not exist (see below), and the review is
# not inserted.
#
# Returns: 1 if the review was successfully added, returns
#          0 if not (e.g. if the movie does not exist, or if
#          an internal error occurred).
#
def add_review(dbConn, movie_id, rating):
  sql = """Insert into Ratings(Movie_ID, Rating) 
           Values(?, ?);"""
  rows = datatier.perform_action(dbConn, sql, [movie_id, rating])

  if rows == -1 or rows == 0:
    return 0
  else:
    return 1

##################################################################
#
# set_tagline:
#
# Sets the tagline --- summary --- for the given movie. If
# the movie already has a tagline, it will be replaced by
# this new value. Passing a tagline of "" effectively 
# deletes the existing tagline. It is considered an error
# if the movie does not exist (see below), and the tagline
# is not set.
#
# Returns: 1 if the tagline was successfully set, returns
#          0 if not (e.g. if the movie does not exist, or if
#          an internal error occurred).
#
def set_tagline(dbConn, movie_id, tagline):
  sql = """Update Movie_Taglines
           set Tagline = ?
           where Movie_ID = ?"""
  
  rows = datatier.perform_action(dbConn, sql, 
                                 [tagline, movie_id])

  if rows == -1 or rows == 0:
    return 0
  else:
    return 1