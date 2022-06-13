<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>Jsp Test Project1</title>
    <link rel="stylesheet" href="../styles/update.css">
    <script src="../scripts/update.js"></script>
</head>
<body>
<h1><%= "Jsp Test Project1" %></h1>
<hr>

<form class="form" action="">
    <label for="product-id">Product ID:</label>
    <input type="text" id="product-id" name="product-id"><br>
    <label for="product-name">Product name:</label>
    <input type="text" id="product-name" name="product-name"><br>
    <label for="product-price">Product price:</label>
    <input type="text" id="product-price" name="product-price"><br>
    <button type="button" onclick="onSubmitButtonClicked()">Update Product</button>
</form>
</body>
</html>