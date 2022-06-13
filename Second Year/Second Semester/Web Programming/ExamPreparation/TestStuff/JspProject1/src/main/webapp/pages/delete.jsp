<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>Jsp Test Project1</title>
    <link rel="stylesheet" href="../styles/delete.css">
    <script src="../scripts/delete.js"></script>
</head>
<body>
<h1><%= "Jsp Test Project1" %></h1>
<hr>

<form class="form" action="">
    <label for="product-id">Product ID:</label>
    <input type="text" id="product-id" name="product-id"><br>
    <button type="button" onclick="onSubmitButtonClicked()">Update Product</button>
</form>
</body>
</html>