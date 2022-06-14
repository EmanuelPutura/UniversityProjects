package web.test.jspproject1.controller;

import org.json.JSONObject;
import web.test.jspproject1.model.Product;
import web.test.jspproject1.service.ProductService;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

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

        if ("insert".equals(action)) {
            handleInsertPost(request, response);
        }
    }

    protected void doPut(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        var bufferedReader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        var data = bufferedReader.readLine();
        var jsonParams = new JSONObject(data);

        var action = jsonParams.getString("action");

        if ("update".equals(action)) {
            handleUpdatePut(request, response, jsonParams);
        }
    }

    protected void doDelete(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        var bufferedReader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        var data = bufferedReader.readLine();
        var jsonParams = new JSONObject(data);

        var action = jsonParams.getString("action");

        if ("delete".equals(action)) {
            handleDeleteDelete(request, response, jsonParams);
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

    private void handleUpdatePut(HttpServletRequest request, HttpServletResponse response, JSONObject jsonParams) throws IOException {
        var id = jsonParams.getInt("productId");
        var name = jsonParams.getString("productName");
        var price = jsonParams.getInt("productPrice");

        productService.update(new Product(id, name , price));
    }

    private void handleDeleteDelete(HttpServletRequest request, HttpServletResponse response, JSONObject jsonParams) throws IOException {
        var id = jsonParams.getInt("productId");
        productService.delete(id);
    }
}

