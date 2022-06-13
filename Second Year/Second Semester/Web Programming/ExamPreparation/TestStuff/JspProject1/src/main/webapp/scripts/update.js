function onSubmitButtonClicked() {
    const productID = document.getElementById("product-id").value;
    const productName = document.getElementById("product-name").value;
    const productPrice = document.getElementById("product-price").value;

    const requestContent = {"action": "update", "productId": productID, "productName": productName, "productPrice": productPrice};
    const putRequestBody = JSON.stringify(requestContent);

    const putRequest = new XMLHttpRequest();

    putRequest.open("PUT", "../crud");
    putRequest.setRequestHeader("Content-type", "application/json");
    putRequest.send(putRequestBody);

    putRequest.onload = function() {
        document.location.href = "../index.jsp";
    }
}
