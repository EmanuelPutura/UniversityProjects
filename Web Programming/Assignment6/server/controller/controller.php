<?php

require_once "../view/view.php";

class Controller {
    private $view;

    public function __construct() {
        $this->view = new View();
    }

    public function serve() {
        if (isset($_POST["func"])) {
            $function = $_POST["func"];
            switch($function) {
                case "insert":
                    $this->serveInsert();
                    break;
                case "update":
                    $this->serveUpdate();
                    break;
                case "delete":
                    $this->serveDelete();
                    break;
                default:
                    return;
            }
        }
    }

    private function serveInsert() {
        if (!isset($_POST["productName"]) || !isset($_POST["productCategory"]) || !isset($_POST["productPrice"]))
            return;
        
        $productName = $_POST["productName"];
        $productCategory = $_POST["productCategory"];
        $productPrice = $_POST["productPrice"];

        $this->view->insertProduct($productName, $productCategory, $productPrice);
    }

    private function serveUpdate() {
        die("update");
    }

    private function serveDelete() {
        die("delete");
    }
}

$controller = new Controller();
$controller->serve();
?>

