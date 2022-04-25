import datetime
from tkinter import *
from tkinter import messagebox

from domain.client import Client
from domain.movie import Movie
from erros.exceptions import ValidationError, IDError, RepositoryError, ServiceError, UndoRedoError
from services.undo_redo_handlers import UndoHandlerEnum
from services.undo_redo_service import UndoManager, RedoManager


class GUI:
    def __init__(self, movie_service, client_service, rental_service):
        self.__movie_service = movie_service
        self.__client_service = client_service
        self.__rental_service = rental_service
        self.__root = Tk()
        self.__frame = Frame(self.__root)

    def __configure_movies_interface(self):
        self.__delete_widgets()
        self.__entities = self.__movie_service.get_all_movies()

        self.__title_label = [''] * 5
        self.__title_entry = [''] * 5
        self.__description_label = [''] * 5
        self.__description_entry = [''] * 5
        self.__genre_label = [''] * 5
        self.__genre_entry = [''] * 5

        self.__configure_movie_labels(1, 2)
        self.__configure_movie_labels(2, 2)
        self.__configure_movie_buttons()

        self.__id_label1 = Label(self.__root, text='Movie ID:', font='bold 10', pady=3)
        self.__id_label1.grid(column=0, row=0)
        self.__id_entry1 = Entry(self.__root, font='bold 10')
        self.__id_entry1.grid(column=1, row=0)
        self.__configure_movie_labels(0, 2)

        self.__id_label2 = Label(self.__root, text='Movie ID:', font='bold 10', pady=3)
        self.__id_label2.grid(column=6, row=3)
        self.__id_entry2 = Entry(self.__root, font='bold 10')
        self.__id_entry2.grid(column=7, row=3)

        self.__id_entry3 = Label(self.__root, text='Movie ID:', font='bold 10', pady=3)
        self.__id_entry3.grid(column=0, row=2)
        self.__id_entry3 = Entry(self.__root, font='bold 10')
        self.__id_entry3.grid(column=1, row=2)

        self.__text = Text(self.__root, font='bold 10', width=130)
        self.__text.grid(columnspan=9, pady=20, padx=20)
        self.__text.configure(font='bold 10')

    def __configure_movie_buttons(self):
        add_button = Button(self.__root, text='Add movie', font='bold 10', width=15, command=self.__add_movie_button_pressed)
        add_button.grid(column=8, row=1, padx=20)
        update_button = Button(self.__root, text='Update movie', font='bold 10', width=15, command=self.__update_movie_button)
        update_button.grid(column=8, row=2, padx=20)
        search_button = Button(self.__root, text='Search movie', font='bold 10', width=15, command=self.__search_movie_button_pressed)
        search_button.grid(column=8, row=0, padx=20)
        remove_button = Button(self.__root, text='Remove movie', font='bold 10', width=15, command=self.__remove_movie_button_pressed)
        remove_button.grid(column=8, row=3, padx=20)
        list_button = Button(self.__root, text='List movies', font='bold 10', width=50, command=self.__list_button_pressed)
        list_button.grid(column=0, row=4, columnspan=4, padx=30)
        statistics_button = Button(self.__root, text='Provide movie statistics', font='bold 10', width=50, command=self.__movies_statistics_button_pressed)
        statistics_button.grid(column=5, row=4, columnspan=4, padx=30)

    def __configure_movie_labels(self, row, column=0):
        self.__title_label[row] = Label(self.__root, text='Title:', font='bold 10', pady=3)
        self.__title_label[row].grid(column=column, row=row)
        self.__title_entry[row] = Entry(self.__root, font='bold 10')
        self.__title_entry[row].grid(column=column + 1, row=row)
        self.__description_label[row] = Label(self.__root, text='Description:', font='bold 10', pady=3)
        self.__description_label[row].grid(column=column + 2, row=row)
        self.__description_entry[row] = Entry(self.__root, font='bold 10')
        self.__description_entry[row].grid(column=column + 3, row=row)
        self.__genre_label[row] = Label(self.__root, text='Genre:', font='bold 10', pady=3)
        self.__genre_label[row].grid(column=column + 4, row=row)
        self.__genre_entry[row] = Entry(self.__root, font='bold 10')
        self.__genre_entry[row].grid(column=column + 5, row=row)

    def __configure_clients_interface(self):
        self.__delete_widgets()
        self.__entities = self.__client_service.get_all_clients()

        self.__id_label1 = Label(self.__root, text='Client ID:', font='bold 10', pady=3)
        self.__id_label1.grid(column=0, row=0)
        self.__id_entry1 = Entry(self.__root, font='bold 10')
        self.__id_entry1.grid(column=1, row=0)
        self.__name_label1 = Label(self.__root, text='Name:', font='bold 10', pady=3)
        self.__name_label1.grid(column=2, row=0)
        self.__name_entry1 = Entry(self.__root, font='bold 10')
        self.__name_entry1.grid(column=3, row=0)
        search_button = Button(self.__root, text='Search client', font='bold 10', width=15, command=self.__search_client_button_pressed)
        search_button.grid(column=4, row=0, padx=20)

        self.__name_label2 = Label(self.__root, text='Name:', font='bold 10', pady=3)
        self.__name_label2.grid(column=2, row=1)
        self.__name_entry2 = Entry(self.__root, font='bold 10')
        self.__name_entry2.grid(column=3, row=1)
        add_button = Button(self.__root, text='Add client', font='bold 10', width=15, command=self.__add_client_button_pressed)
        add_button.grid(column=4, row=1, padx=20)

        self.__id_label2 = Label(self.__root, text='Client ID:', font='bold 10', pady=3)
        self.__id_label2.grid(column=0, row=2)
        self.__id_entry2 = Entry(self.__root, font='bold 10')
        self.__id_entry2.grid(column=1, row=2)
        self.__name_label3 = Label(self.__root, text='Name:', font='bold 10', pady=3)
        self.__name_label3.grid(column=2, row=2)
        self.__name_entry3 = Entry(self.__root, font='bold 10')
        self.__name_entry3.grid(column=3, row=2)
        update_button = Button(self.__root, text='Update client', font='bold 10', width=15, command=self.__update_client_button_pressed)
        update_button.grid(column=4, row=2, padx=20)

        self.__id_label3 = Label(self.__root, text='Client ID:', font='bold 10', pady=3)
        self.__id_label3.grid(column=2, row=3)
        self.__id_entry3 = Entry(self.__root, font='bold 10')
        self.__id_entry3.grid(column=3, row=3)
        remove_button = Button(self.__root, text='Remove client', font='bold 10', width=15, command=self.__remove_client_button_pressed)
        remove_button.grid(column=4, row=3, padx=20)

        list_button = Button(self.__root, text='List clients', font='bold 10', width=20, command=self.__list_button_pressed)
        list_button.grid(column=0, row=4, columnspan=2, padx=10)
        statistics_button = Button(self.__root, text='Provide client statistics', font='bold 10', width=20, command=self.__clients_statistics_button_pressed)
        statistics_button.grid(column=3, row=4, columnspan=2, padx=10)

        self.__text = Text(self.__root, font='bold 10', width=75)
        self.__text.grid(columnspan=9, pady=20, padx=20)
        self.__text.configure(font='bold 10')

    def __configure_rentals_interface(self):
        self.__delete_widgets()
        self.__entities = self.__rental_service.get_all_rentals()

        self.__movie_id_label1 = Label(self.__root, text='Movie ID:', font='bold 10', pady=3)
        self.__movie_id_label1.grid(row=0, column=0)
        self.__movie_id_entry1 = Entry(self.__root, font='bold 10')
        self.__movie_id_entry1.grid(row=0, column=1)
        self.__client_id_label1 = Label(self.__root, text='Client ID:', font='bold 10', pady=3)
        self.__client_id_label1.grid(row=0, column=2)
        self.__client_id_entry1 = Entry(self.__root, font='bold 10')
        self.__client_id_entry1.grid(row=0, column=3)
        self.__rented_date_label = Label(self.__root, text='Rented date:', font='bold 10', pady=3)
        self.__rented_date_label.grid(row=0, column=4)
        self.__rented_date_entry = Entry(self.__root, font='bold 10')
        self.__rented_date_entry.grid(row=0, column=5)
        self.__due_date_label = Label(self.__root, text='Due date:', font='bold 10', pady=3)
        self.__due_date_label.grid(row=0, column=6)
        self.__due_date_entry = Entry(self.__root, font='bold 10')
        self.__due_date_entry.grid(row=0, column=7)
        rent_button = Button(self.__root, text='Rent', font='bold 10', width=20, command=self.__rent_button_pressed)
        rent_button.grid(row=0, column=8, padx=10)

        self.__movie_id_label2 = Label(self.__root, text='Movie ID:', font='bold 10', pady=3)
        self.__movie_id_label2.grid(row=1, column=0)
        self.__movie_id_entry2 = Entry(self.__root, font='bold 10')
        self.__movie_id_entry2.grid(row=1, column=1)
        self.__client_id_label2 = Label(self.__root, text='Client ID:', font='bold 10', pady=3)
        self.__client_id_label2.grid(row=1, column=2)
        self.__client_id_entry2 = Entry(self.__root, font='bold 10')
        self.__client_id_entry2.grid(row=1, column=3)
        self.__returned_date_label = Label(self.__root, text='Returned date:', font='bold 10', pady=3)
        self.__returned_date_label.grid(row=1, column=4)
        self.__returned_date_entry = Entry(self.__root, font='bold 10')
        self.__returned_date_entry.grid(row=1, column=5)
        return_button = Button(self.__root, text='Return', font='bold 10', width=20, command=self.__return_button_pressed)
        return_button.grid(row=1, column=8, padx=10)

        statistics_button = Button(self.__root, text='Provide rental statistics', font='bold 10', width=125, command=self.__rentals_statistics_button_pressed)
        statistics_button.grid(row=2, column=0, columnspan=9, padx=30)

        self.__text = Text(self.__root, font='bold 10', width=130)
        self.__text.grid(columnspan=9, pady=20, padx=20)
        self.__text.configure(font='bold 10')

    def __undo(self):
        try:
            UndoManager.undo()
            if isinstance(self.__entities[0], Movie):
                self.__entities = self.__movie_service.get_all_movies()
            elif isinstance(self.__entities[0], Client):
                self.__entities = self.__client_service.get_all_clients()
        except UndoRedoError as undoRedoError:
            messagebox.showinfo('UndoRedoError', undoRedoError.gui_str())

    def __redo(self):
        try:
            RedoManager.redo()
            if isinstance(self.__entities[0], Movie):
                self.__entities = self.__movie_service.get_all_movies()
            elif isinstance(self.__entities[0], Client):
                self.__entities = self.__client_service.get_all_clients()
        except UndoRedoError as undoRedoError:
            messagebox.showinfo('UndoRedoError', undoRedoError.gui_str())

    def __delete_widgets(self):
        for widget in self.__root.grid_slaves():
            widget.destroy()

    def __init_configure(self):
        self.__root.title('MovieRental Application')
        self.__frame.grid()
        self.__configure_movies_interface()
        main_menu = Menu(self.__root)
        main_menu.add_command(label='Movie commands', command=self.__configure_movies_interface)
        main_menu.add_command(label='Client commands', command=self.__configure_clients_interface)
        main_menu.add_command(label='Rental commands', command=self.__configure_rentals_interface)
        main_menu.add_command(label='Undo', command=self.__undo)
        main_menu.add_command(label='Redo', command=self.__redo)
        main_menu.add_command(label='Exit', command=self.__root.quit)
        self.__root.config(menu=main_menu)

    def __list_entities(self, entity_text, entities):
        self.__text.config(state=NORMAL)
        self.__text.delete('1.0', END)
        for entity in entities:
            entity_text.insert(INSERT, entity.gui_str())
        self.__text.config(state=DISABLED)

    def __list_button_pressed(self):
        self.__text.config(state=NORMAL)
        self.__text.delete('1.0', END)
        self.__list_entities(self.__text, self.__entities)
        self.__text.config(state=DISABLED)

    def __movies_statistics_button_pressed(self):
        movie_dtos = self.__rental_service.find_most_rented_movies()
        self.__text.config(state=NORMAL)
        self.__text.delete('1.0', END)
        self.__list_entities(self.__text, movie_dtos)
        self.__text.config(state=DISABLED)

    def __clients_statistics_button_pressed(self):
        client_dtos = self.__rental_service.find_most_active_clients()
        self.__text.config(state=NORMAL)
        self.__text.delete('1.0', END)
        self.__list_entities(self.__text, client_dtos)
        self.__text.config(state=DISABLED)

    def __rentals_statistics_button_pressed(self):
        movie_dtos = self.__rental_service.find_late_rentals()
        self.__text.config(state=NORMAL)
        self.__text.delete('1.0', END)
        self.__list_entities(self.__text, movie_dtos)
        self.__text.config(state=DISABLED)

    def __add_movie_button_pressed(self):
        try:
            added_movie = self.__movie_service.add_movie(self.__title_entry[1].get(), self.__description_entry[1].get(), self.__genre_entry[1].get())
            UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.ADD_MOVIE, added_movie.id,
                                           self.__rental_service)
            self.__entities = self.__movie_service.get_all_movies()
        except ValidationError as validationError:
            messagebox.showinfo('ValidationError', validationError.gui_str())
            return
        except RepositoryError as repositoryError:
            messagebox.showinfo('RepositoryError', repositoryError.gui_str())
            return
        except IDError as idError:
            messagebox.showinfo('IDError', idError.gui_str())
            return
        except ServiceError as serviceError:
            messagebox.showinfo('ServiceError', serviceError.gui_str())
            return
        except Exception as exception:
            messagebox.showinfo('Unexpected exception', exception)
            return

    def __add_client_button_pressed(self):
        try:
            added_client = self.__client_service.add_client(self.__name_entry2.get())
            UndoManager.register_operation(self.__client_service, UndoHandlerEnum.ADD_CLIENT, added_client.id,
                                           self.__rental_service)
            self.__entities = self.__client_service.get_all_clients()
        except ValidationError as validationError:
            messagebox.showinfo('ValidationError', validationError.gui_str())
            return
        except RepositoryError as repositoryError:
            messagebox.showinfo('RepositoryError', repositoryError.gui_str())
            return
        except IDError as idError:
            messagebox.showinfo('IDError', idError.gui_str())
            return
        except ServiceError as serviceError:
            messagebox.showinfo('ServiceError', serviceError.gui_str())
            return
        except Exception as exception:
            messagebox.showinfo('Unexpected exception', exception)
            return

    def __remove_movie_button_pressed(self):
        try:
            movie_id = self.__id_entry2.get()
            if not movie_id.isdigit():
                raise IDError("'{}' is not a valid ID.\n".format(movie_id))
            removed_movie = self.__movie_service.get_movie(int(movie_id))
            self.__movie_service.remove_movie(int(movie_id))
            removed_rentals = self.__rental_service.remove_movie_rentals(int(movie_id))
            UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.REMOVE_MOVIE, removed_movie, removed_rentals, self.__rental_service)
            self.__entities = self.__movie_service.get_all_movies()
        except ValidationError as validationError:
            messagebox.showinfo('ValidationError', validationError.gui_str())
            return
        except RepositoryError as repositoryError:
            messagebox.showinfo('RepositoryError', repositoryError.gui_str())
            return
        except IDError as idError:
            messagebox.showinfo('IDError', idError.gui_str())
            return
        except ServiceError as serviceError:
            messagebox.showinfo('ServiceError', serviceError.gui_str())
            return
        except Exception as exception:
            messagebox.showinfo('Unexpected exception', exception)
            return

    def __remove_client_button_pressed(self):
        try:
            client_id = self.__id_entry3.get()
            if not client_id.isdigit():
                raise IDError("'{}' is not a valid ID.\n".format(client_id))
            removed_client = self.__client_service.get_client(int(client_id))
            self.__client_service.remove_client(int(client_id))
            removed_rentals = self.__rental_service.remove_client_rentals(int(client_id))
            UndoManager.register_operation(self.__client_service, UndoHandlerEnum.REMOVE_CLIENT, removed_client,
                                           removed_rentals, self.__rental_service)
            self.__entities = self.__client_service.get_all_clients()
        except ValidationError as validationError:
            messagebox.showinfo('ValidationError', validationError.gui_str())
            return
        except RepositoryError as repositoryError:
            messagebox.showinfo('RepositoryError', repositoryError.gui_str())
            return
        except IDError as idError:
            messagebox.showinfo('IDError', idError.gui_str())
            return
        except ServiceError as serviceError:
            messagebox.showinfo('ServiceError', serviceError.gui_str())
            return
        except Exception as exception:
            messagebox.showinfo('Unexpected exception', exception)
            return

    def __update_movie_button(self):
        try:
            movie_id = self.__id_entry3.get()
            if not movie_id.isdigit():
                raise IDError("'{}' is not a valid ID.\n".format(movie_id))
            movie = self.__movie_service.get_movie(int(movie_id))
            if self.__title_entry[2].get() != '':
                UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.UPDATE_MOVIE_TITLE, movie.id, movie.title)
                self.__movie_service.update_title(int(movie_id), self.__title_entry[2].get())
            elif self.__description_entry[2].get() != '':
                UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.UPDATE_MOVIE_DESCRIPTION, movie.id, movie.description)
                self.__movie_service.update_description(int(movie_id), self.__description_entry[2].get())
            elif self.__genre_entry[2].get() != '':
                UndoManager.register_operation(self.__movie_service, UndoHandlerEnum.UPDATE_MOVIE_GENRE, movie.id, movie.genre)
                self.__movie_service.update_genre(int(movie_id), self.__genre_entry[2].get())
            else:
                messagebox.showinfo('Error', 'No data inserted.')
                return
            self.__entities = self.__movie_service.get_all_movies()
        except ValidationError as validationError:
            messagebox.showinfo('ValidationError', validationError.gui_str())
            return
        except RepositoryError as repositoryError:
            messagebox.showinfo('RepositoryError', repositoryError.gui_str())
            return
        except IDError as idError:
            messagebox.showinfo('IDError', idError.gui_str())
            return
        except ServiceError as serviceError:
            messagebox.showinfo('ServiceError', serviceError.gui_str())
            return
        except Exception as exception:
            messagebox.showinfo('Unexpected exception', exception)
            return

    def __update_client_button_pressed(self):
        try:
            client_id = self.__id_entry2.get()
            if not client_id.isdigit():
                raise IDError("'{}' is not a valid ID.\n".format(client_id))
            if self.__name_entry3.get() != '':
                client = self.__client_service.get_client(int(client_id))
                UndoManager.register_operation(self.__client_service, UndoHandlerEnum.UPDATE_CLIENT_NAME, client.id,
                                               client.name)
                self.__client_service.update_name(int(client_id), self.__name_entry3.get())
            else:
                messagebox.showinfo('Error', 'No data inserted.')
                return
            self.__entities = self.__client_service.get_all_clients()
        except IDError as idError:
            messagebox.showinfo('IDError', idError.gui_str())
            return
        except ValidationError as validationError:
            messagebox.showinfo('ValidationError', validationError.gui_str())
            return
        except RepositoryError as repositoryError:
            messagebox.showinfo('RepositoryError', repositoryError.gui_str())
            return
        except ServiceError as serviceError:
            messagebox.showinfo('ServiceError', serviceError.gui_str())
            return
        except Exception as exception:
            messagebox.showinfo('Unexpected exception', exception)
            return

    def __search_movie_button_pressed(self):
        entities = []
        if self.__id_entry1.get() != '':
            entities = self.__movie_service.search_by_id(self.__id_entry1.get())
        elif self.__title_entry[0].get() != '':
            entities = self.__movie_service.search_by_title(self.__title_entry[0].get())
        elif self.__description_entry[0].get() != '':
            entities = self.__movie_service.search_by_description(self.__description_entry[0].get())
        elif self.__genre_entry[0].get() != '':
            entities = self.__movie_service.search_by_genre(self.__genre_entry[0].get())
        else:
            messagebox.showinfo('Error', 'No data inserted.')
            return
        if not len(entities):
            messagebox.showinfo('Error', 'No movies found.')
        self.__list_entities(self.__text, entities)

    def __search_client_button_pressed(self):
        entities = []
        if self.__id_entry1.get() != '':
            entities = self.__client_service.search_by_id(self.__id_entry1.get())
        elif self.__name_entry1.get() != '':
            entities = self.__client_service.search_by_name(self.__name_entry1.get())
        else:
            messagebox.showinfo('Error', 'No data inserted.')
            return
        if not len(entities):
            messagebox.showinfo('Error', 'No clients found.')
        self.__list_entities(self.__text, entities)

    def __rent_button_pressed(self):
        movie_id = self.__movie_id_entry1.get()
        client_id = self.__client_id_entry1.get()
        rented_date = self.__rented_date_entry.get()
        due_date = self.__due_date_entry.get()

        try:
            if not movie_id.isdigit() or self.__movie_service.get_movie(int(movie_id)) is None:
                raise IDError("'{}' is not a valid ID.\n".format(movie_id))
            if not client_id.isdigit() or self.__client_service.get_client(int(client_id)) is None:
                raise IDError("'{}' is not a valid ID.\n".format(client_id))
            rented_date = datetime.datetime.strptime(rented_date, '%d/%m/%Y').date()
            due_date = datetime.datetime.strptime(due_date, '%d/%m/%Y').date()
            added_rental = self.__rental_service.add_rental(int(movie_id), int(client_id), rented_date, due_date)
            UndoManager.register_operation(self.__rental_service, UndoHandlerEnum.RENT_MOVIE, added_rental.id)
        except IDError as idError:
            messagebox.showinfo('IDError', idError.gui_str())
            return
        except ValidationError as validationError:
            messagebox.showinfo('ValidationError', validationError.gui_str())
            return
        except RepositoryError as repositoryError:
            messagebox.showinfo('RepositoryError', repositoryError.gui_str())
            return
        except ServiceError as serviceError:
            messagebox.showinfo('ServiceError', serviceError.gui_str())
            return
        except Exception as exception:
            messagebox.showinfo('Unexpected exception', exception)
            return

    def __return_button_pressed(self):
        movie_id = self.__movie_id_entry2.get()
        client_id = self.__client_id_entry2.get()
        returned_date = self.__returned_date_entry.get()

        try:
            if not movie_id.isdigit() or self.__movie_service.get_movie(int(movie_id)) is None:
                raise IDError("'{}' is not a valid ID.\n".format(movie_id))
            if not client_id.isdigit() or self.__client_service.get_client(int(client_id)) is None:
                raise IDError("'{}' is not a valid ID.\n".format(client_id))
            returned_date = datetime.datetime.strptime(returned_date, '%d/%m/%Y').date()
            rental_id = self.__rental_service.find_and_update_rental(int(client_id), int(movie_id), returned_date)
            UndoManager.register_operation(self.__rental_service, UndoHandlerEnum.RETURN_MOVIE, rental_id)
        except IDError as idError:
            messagebox.showinfo('IDError', idError.gui_str())
            return
        except ValidationError as validationError:
            messagebox.showinfo('ValidationError', validationError.gui_str())
            return
        except RepositoryError as repositoryError:
            messagebox.showinfo('RepositoryError', repositoryError.gui_str())
            return
        except ServiceError as serviceError:
            messagebox.showinfo('ServiceError', serviceError.gui_str())
            return
        except Exception as exception:
            messagebox.showinfo('Unexpected exception', exception)
            return

    def __ui_test_values(self):
        self.__rental_service.add_rental(1, 1, datetime.date(2020, 11, 22), datetime.date(2020, 11, 30),
                                         datetime.date(2020, 12, 1))
        self.__rental_service.add_rental(2, 2, datetime.date(2020, 11, 27), datetime.date(2021, 1, 25))
        self.__rental_service.find_and_update_rental(2, 2, datetime.date(2022, 3, 27))

    def run(self):
        self.__init_configure()
        # self.__ui_test_values()
        self.__root.mainloop()
