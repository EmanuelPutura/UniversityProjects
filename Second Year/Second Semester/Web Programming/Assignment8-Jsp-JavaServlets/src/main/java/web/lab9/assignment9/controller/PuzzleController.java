package web.lab9.assignment9.controller;

import org.json.JSONArray;
import web.lab9.assignment9.exceptions.AppException;
import web.lab9.assignment9.repository.pieces.PiecesRepositoryFactory;
import web.lab9.assignment9.service.PiecesService;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.io.PrintWriter;

import org.json.JSONObject;

@WebServlet(name = "PuzzleServlet", value = "/puzzle-controller")
public class PuzzleController extends HttpServlet {
    private PiecesService piecesService;
    private String lastUsername;

    @Override
    public void init() throws ServletException {
        super.init();

        ServletContext context = getServletContext();
        String realPath = context.getRealPath("\\resources");
        piecesService = new PiecesService(PiecesRepositoryFactory.getInstance(realPath + "\\database.properties"));
        lastUsername = "";
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        HttpSession session = request.getSession();
        var obj = session.getAttribute("user");
        if (!(obj instanceof String username) || obj.equals("")) {
            return;
        }

        var action = request.getParameter("action");
        response.setContentType("application/json");

        if (!lastUsername.equals(username) && !lastUsername.equals("")) {
            piecesService.restartPuzzle();
        }

        lastUsername = username;

        switch (action) {
            case "fetch":
                try {
                    var pieces = piecesService.findAll();

                    JSONArray jsonPieces = new JSONArray();
                    for (var piece : pieces) {
                        JSONObject jsonPiece = new JSONObject();

                        jsonPiece.put("htmlId", piece.getHtmlId());
                        jsonPiece.put("cssBackgroundImg", piece.getCssBackgroundImgUrl());

                        jsonPieces.put(jsonPiece);
                    }

                    var responseOut = new PrintWriter(response.getOutputStream());
                    responseOut.println(jsonPieces);
                    responseOut.flush();
                } catch (AppException ignored) {
                }
                break;
            case "click":
                var responseOut = new PrintWriter(response.getOutputStream());
                responseOut.println(piecesService.onPuzzleCellClicked(request.getParameter("htmlId")));
                responseOut.flush();
                break;
            case "disconnect":
                request.getSession().invalidate();

                RequestDispatcher requestDispatcher = request.getRequestDispatcher("/index.jsp");
                if (requestDispatcher != null) {
                    try {
                        requestDispatcher.forward(request, response);
                    } catch (ServletException e) {
                        e.printStackTrace();
                    }
                }

                piecesService.restartPuzzle();
                break;
        }
    }
}
