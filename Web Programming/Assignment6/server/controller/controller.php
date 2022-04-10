<?php

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
            if (isset($sentData["func"]) && $sentData["func"] === "update")
                $this->serveUpdate($sentData);
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

