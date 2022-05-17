<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
    <head>
        <title>Web - Assignment 9</title>
        <link rel="stylesheet" href="styles/login.css">
    </head>
    <body>
        <form id="login-form" action="${pageContext.request.contextPath}/login-controller" method="post">
            Enter username : <input type="text" name="username"> <BR>
            Enter password : <input type="password" name="password"> <BR>
            <input type="submit" value="Login"/>
        </form>

        <%
            String error = ((String) request.getSession().getAttribute("error"));
            if (error == null) {
                error = "";
            }

//            out.println("<div> Hello </div>");
        %>

        <div><%=error%></div>
    </body>
</html>
