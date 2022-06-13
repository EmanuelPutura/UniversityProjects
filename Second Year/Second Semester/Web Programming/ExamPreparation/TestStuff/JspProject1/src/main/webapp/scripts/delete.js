function onSubmitButtonClicked() {
    const productID = document.getElementById("product-id").value;
    const requestContent = {"action": "delete", "productId": productID};
    const deleteRequestBody = JSON.stringify(requestContent);
    const deleteRequest = new XMLHttpRequest();

    deleteRequest.open("DELETE", "../crud");
    deleteRequest.setRequestHeader("Content-type", "application/json");
    deleteRequest.send(deleteRequestBody);

    deleteRequest.onload = function() {
        document.location.href = "../index.jsp";
    }
}
