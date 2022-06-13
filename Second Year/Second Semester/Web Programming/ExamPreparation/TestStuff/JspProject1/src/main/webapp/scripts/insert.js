function onSubmitButtonClicked() {
    const productName = document.getElementById("product-name").value;
    const productPrice = document.getElementById("product-price").value;

    const postRequestBody = "action=insert&productName=" + productName + "&productPrice=" + productPrice;
    const postRequest = new XMLHttpRequest();

    postRequest.open("POST", "../crud");
    postRequest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    postRequest.send(postRequestBody);

    postRequest.onload = function() {
        document.location.href = "../index.jsp";
    }
}
