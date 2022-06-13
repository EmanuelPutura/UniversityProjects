<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>Jsp Test Project1</title>
    <link rel="stylesheet" href="../styles/insert.css">
    <script src="../scripts/insert.js"></script>
</head>
<body>
<h1><%= "Jsp Test Project1" %></h1>
<hr>

<form class="form">
    <label for="product-name">Product name:</label>
    <input type="text" id="product-name" name="product-name"><br>
    <label for="product-price">Product price:</label>
    <input type="text" id="product-price" name="product-price"><br>
    <button type="button" onclick="onSubmitButtonClicked();">Insert Product</button>
</form>
</body>
</html>