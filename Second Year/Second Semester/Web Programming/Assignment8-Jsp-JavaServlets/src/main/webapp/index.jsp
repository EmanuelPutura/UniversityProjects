<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
    <head>
        <title>Web - Assignment 9</title>
    </head>
    <body>
        <form action="${pageContext.request.contextPath}/login-servlet" method="post">
            Enter username : <input type="text" name="username"> <BR>
            Enter password : <input type="password" name="password"> <BR>
            <input type="submit" value="Login"/>
        </form>
    </body>
</html>
