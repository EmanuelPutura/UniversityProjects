package web.lab9.assignment9.controller;

import web.lab9.assignment9.repository.users.UsersRepositoryFactory;
import web.lab9.assignment9.service.UsersService;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet(name = "UsersServlet", value = "/login-controller")
public class UsersController extends HttpServlet {
    private UsersService usersService;

    @Override
    public void init() throws ServletException {
        super.init();

        ServletContext context = getServletContext();
        String realPath = context.getRealPath("\\resources");
        usersService = new UsersService(UsersRepositoryFactory.getInstance(realPath + "\\database.properties"));
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        RequestDispatcher requestDispatcher = null;
        if (usersService.checkPassword(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("user", username);

            requestDispatcher = request.getRequestDispatcher("/puzzle.jsp");
        }
        else {
            HttpSession session = request.getSession();
            session.setAttribute("error", "Invalid password or username!");

            requestDispatcher = request.getRequestDispatcher(".");
        }

        if (requestDispatcher != null) {
            requestDispatcher.forward(request, response);
        }
    }
}
