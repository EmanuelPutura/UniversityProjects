<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
    <head>
        <title>Web - Assignment 9 - Puzzle</title>
        <link rel="stylesheet" href="styles/puzzle.css">
        <script src="scripts/puzzle.js"></script>
    </head>
    <body>
        <%
            HttpSession currentSession = request.getSession();
            Object obj = currentSession.getAttribute("user");
            if (!(obj instanceof String) || ((String) obj).equals("")) {
                RequestDispatcher requestDispatcher = request.getRequestDispatcher("/index.jsp");
                if (requestDispatcher != null) {
                    try {
                        requestDispatcher.forward(request, response);
                    } catch (ServletException ignored) {}
                }
            }

            String username = ((String) request.getSession().getAttribute("user"));
        %>

        <h1 id="title">Hello, <%=username%>!</h1>

        <div id="puzzle-table">
        </div>

        <button id="disconnect-button" onclick="onLogoutButtonClicked()" type="button">Logout</button>
    </body>
</html>
