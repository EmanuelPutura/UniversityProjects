from domain.movie import Movie
from random import randint


class MovieService:
    """
    Service class for the Movie class
    """
    def __init__(self, movie_validator, movie_repository):
        self.__movie_validator = movie_validator
        self.__movie_repository = movie_repository

    def add_movie(self, title, description, genre):
        """
        Adds a new movie
        :param title: a new title for the movie
        :param description: a new description for the movie
        :param genre: a new genre for the movie
        :return: the added movie
        """
        movie = Movie(title, description, genre)
        self.__movie_validator.validate(movie)
        self.__movie_repository.add(movie)
        return movie

    def remove_movie(self, movie_id):
        """
        Removes a movie, being given its ID
        :param movie_id: the movie's ID
        :return: -
        """
        self.__movie_repository.remove(movie_id)

    def update_title(self, movie_id, title):
        """
        Updates a movie's title, being given its ID
        :param movie_id: the movie's ID
        :param title: the movie's new title
        :return: -
        """
        self.__movie_repository.update_title(movie_id, title)

    def update_description(self, movie_id, description):
        """
        Updates a movie's description, being given its ID
        :param movie_id: the movie's ID
        :param description: the movie's new description
        :return: -
        """
        self.__movie_repository.update_description(movie_id, description)

    def update_genre(self, movie_id, genre):
        """
        Updates a movie's genre, being given its ID
        :param movie_id: the movie's ID
        :param genre: the movie's new description
        :return: -
        """
        self.__movie_repository.update_genre(movie_id, genre)

    def search_by_id(self, id):
        """
        Searches movies by a given ID
        :param id: a given ID
        :return: the list of found movies
        """
        return self.__movie_repository.search_by_id(id)

    def search_by_title(self, title):
        """
        Searches movies by a given title
        :param title: a given title
        :return: the list of found movies
        """
        return self.__movie_repository.search_by_title(title)

    def search_by_description(self, description):
        """
        Searches movies by a given description
        :param description: a given description
        :return: the list of found movies
        """
        return self.__movie_repository.search_by_description(description)

    def search_by_genre(self, genre):
        """
        Searches movies by a given genre
        :param genre: a given genre
        :return: the list of found movies
        """
        return self.__movie_repository.search_by_genre(genre)

    def get_all_movies(self):
        """
        Gets all the existing movies
        :return: all the existing movies
        """
        return self.__movie_repository.entities

    def get_movie(self, movie_id):
        """
        Gets a movie, being given its ID
        :param movie_id: the movie's ID
        :return: the found movie (if it exists)
        """
        return self.__movie_repository.find_by_id(movie_id)

    def generate_movies(self):
        """
        Generates random movies
        """
        number_of_movies = 10
        default_titles = ['Rebecca', 'Star Wars: The Phantom Menace', 'Star Wars: A New Hope', 'Good Will Hunting',
                          'Peaceful Warrior',
                          'Rocky', 'American Sniper', 'Escape from Alcatraz', 'Titanic',
                          'Harry Potter and the Half-Blood Prince',
                          'Harry Potter and the Deathly Hallows – Part 1',
                          'Harry Potter and the Deathly Hallows – Part 2', 'Scooby-Doo',
                          'Glory', 'Iron Man', 'Spider Man', 'The Godfather', 'Before Sunrise',
                          'The Wolf of Wall Street', 'The Last Samurai', 'Lord Of The Rings']
        default_descriptions = ['Boring.', 'Cool.', '10/10.', 'Very boring.', 'Nice one.', 'Terrible.',
                                'Inspiring movie.',
                                'Motivational one.', 'Would watch it again.', 'Educational one.',
                                'Best one I have seen so far.',
                                'Really boring.', 'Best movie.', 'Wow!', 'Worst movie I have seen so far!',
                                'Could have been better.',
                                'Instructive one.', 'Really cool.', 'What a plot-twist!',
                                'Spoiler: It is not worth watching it.']
        default_genres = ['Action', 'Comedy', 'Thriller', 'Romance', 'Adventure', 'Crime', 'Drama', 'Fantasy',
                          'Historical',
                          'Horror',
                          'Mystery', 'Philosophical', 'Political', 'Science fiction', 'Western', 'Urban',
                          'Comedy-drama',
                          'War', 'Biographical', 'Animation']

        movies = self.__movie_repository.entities
        movie_titles = list(map(lambda movie: movie.title, movies))

        for i in range(number_of_movies):
            while True:
                title = default_titles[randint(0, len(default_titles) - 1)]
                if not (title in movie_titles):
                    movie_titles.append(title)
                    break
            description = default_descriptions[randint(0, len(default_descriptions) - 1)]
            genre = default_genres[randint(0, len(default_genres) - 1)]
            self.add_movie(title, description, genre)
