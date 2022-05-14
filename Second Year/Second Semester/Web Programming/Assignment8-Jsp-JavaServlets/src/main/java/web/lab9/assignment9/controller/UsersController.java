package web.lab9.assignment9.controller;

import web.lab9.assignment9.repository.users.UsersRepositoryFactory;
import web.lab9.assignment9.service.UsersService;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "UsersServlet", value = "/login-servlet")
public class UsersController extends HttpServlet {
    private UsersService service;
    private String realPath;

    @Override
    public void init() throws ServletException {
        super.init();

        ServletContext context = getServletContext();
        realPath = context.getRealPath("\\resources");
        service = new UsersService(UsersRepositoryFactory.getInstance(realPath + "\\database.properties"));
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (service.checkPassword(username, password)) {
            System.out.println("Correct!");
        }
        else {
            System.out.println("Wrong!");
        }
    }
}
