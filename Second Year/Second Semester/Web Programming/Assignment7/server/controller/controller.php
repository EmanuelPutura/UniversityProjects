<?php

header('Access-Control-Allow-Origin: *');
header('Access-Control-Allow-Headers: *');
header('Access-Control-Allow-Methods: *');
header('Content-type: application/json');

require_once "../view/view.php";

class Controller {
    private $view;

    public function __construct() {
        $this->view = new View();
    }

    public function serve() {
        if (isset($_POST["func"]) && $_POST["func"] === "insert")
            $this->serveInsert();
        else if (isset($_SERVER['REQUEST_METHOD']) && $_SERVER['REQUEST_METHOD'] === "PUT") {
            $putRequestFile = fopen('php://input', 'r');
            $requestData = '';
    
            while($data = fread($putRequestFile, 1024))
                $requestData .= $data;
            fclose($putRequestFile);

            $sentData = json_decode($requestData, true);
            if (isset($sentData["body"]["func"]) && $sentData["body"]["func"] === "update")
                $this->serveUpdate($sentData["body"]);
        }
        else if (isset($_SERVER['REQUEST_METHOD']) && $_SERVER['REQUEST_METHOD'] === "DELETE") {
            $putRequestFile = fopen('php://input', 'r');
            $requestData = '';
    
            while($data = fread($putRequestFile, 1024))
                $requestData .= $data;
            fclose($putRequestFile);
            
            $sentData = json_decode($requestData, true);
            if (isset($sentData["func"]) && $sentData["func"] === "delete")
                $this->serveDelete($sentData);
        }
        else if (isset($_GET) && isset($_GET["func"]) && $_GET["func"] === "select") {
            $this->serveSelect();
        }
        else if (isset($_GET) && isset($_GET["func"]) && $_GET["func"] === "check" && isset($_GET["id"])) {
            return $this->view->checkProductID((int) $_GET["id"]);
        } 
    }

    private function serveSelect() {
        if (!isset($_GET["category"]) || !isset($_GET["pageSize"]) || !isset($_GET["currentPage"]))
            return;
        
        $this->view->selectProducts($_GET["category"], (int) $_GET["pageSize"], (int) $_GET["currentPage"]);
    }

    private function serveInsert() {
        if (!isset($_POST["productName"]) || !isset($_POST["productCategory"]) || !isset($_POST["productPrice"]))
            return;
    
        $this->view->insertProduct($_POST["productName"], $_POST["productCategory"], (int) $_POST["productPrice"]);
    }

    private function serveUpdate(Array $requestData) {    
        if (!isset($requestData["productID"]) || !isset($requestData["productName"]) || !isset($requestData["productCategory"]) || !isset($requestData["productPrice"]))
            return;

        $this->view->updateProduct((int) $requestData["productID"], $requestData["productName"], $requestData["productCategory"], (int) $requestData["productPrice"]);
    }

    private function serveDelete(Array $requestData) {
        if (!isset($requestData["productID"]))
            return;

        $this->view->deleteProduct((int) $requestData["productID"]);
    }
}

$controller = new Controller();
$controller->serve();
?>

