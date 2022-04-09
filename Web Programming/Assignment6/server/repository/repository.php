<?php
require_once "../model/product.php";

class Repository {
    private $hostname = "localhost";
    private $username = "root";
    private $password = "";
    private $database = "ecommerecestore";
    private $tableName = "products";
    private $connection = NULL;

    public function __construct() {
        $this->connect();
    }

    public function __destruct() {
        $this->connection->close();
    }

    private function connect() {
        $this->connection = new mysqli($this->hostname, $this->username, $this->password, $this->database);
        
        // check connection
        if ($this->connection->connect_error) {
            die("Connection failed: " . $this->connection->connect_error);
        }
    }

    public function insertProduct(Product $product) : bool {
        $productName = $product->getName();
        $productCategory = $product->getCategory();
        $productPrice = (string) $product->getPrice();

        $sqlQuery = "INSERT INTO `" . $this->tableName . "` (`Name`, `Category`, `Price in dollars`) 
                    VALUES ('" . $productName . "', '" . $productCategory . "', '" . $productPrice . "')";

        if ($this->connection->query($sqlQuery) === TRUE)
            return true;
        return false;
    }
}
?>
