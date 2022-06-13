package web.test.jspproject1.controller;

import web.test.jspproject1.model.Product;
import web.test.jspproject1.service.ProductService;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet(name = "CrudServlet", value = "/crud")
public class CrudController extends HttpServlet {
    private ProductService productService;

    @Override
    public void init() throws ServletException {
        super.init();

        productService = new ProductService();
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        var action = request.getParameter("action");

        switch (action) {
            case "insert" -> handleInsertGet(request, response);
            case "update" -> handleUpdateGet(request, response);
            case "delete" -> handleDeleteGet(request, response);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        var action = request.getParameter("action");

        switch (action) {
            case "insert" -> handleInsertPost(request, response);
            case "update" -> handleUpdatePost(request, response);
            case "delete" -> handleDeletePost(request, response);
        }
    }

    private void handleCrudGet(HttpServletRequest request, HttpServletResponse response, String url) throws IOException {
        RequestDispatcher requestDispatcher = request.getRequestDispatcher(url);
        if (requestDispatcher != null) {
            try {
                requestDispatcher.forward(request, response);
            } catch (ServletException e) {
                e.printStackTrace();
            }
        }
    }

    private void handleInsertGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        handleCrudGet(request, response, "/pages/insert.jsp");
    }

    private void handleUpdateGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        handleCrudGet(request, response, "/pages/update.jsp");
    }

    private void handleDeleteGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        handleCrudGet(request, response, "/pages/delete.jsp");
    }

    private void handleInsertPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        var name = request.getParameter("productName");
        var price = request.getParameter("productPrice");
        var intPrice = Integer.parseInt(price);

        productService.save(new Product(-1, name, intPrice));
    }

    private void handleUpdatePost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        System.out.println("Update!");
    }

    private void handleDeletePost(HttpServletRequest request, HttpServletResponse response) throws IOException {

    }
}

