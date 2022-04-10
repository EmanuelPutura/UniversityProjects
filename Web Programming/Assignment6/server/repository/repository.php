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
        $sqlQuery = "INSERT INTO `" . $this->tableName . "` (`Name`, `Category`, `Price in dollars`) 
                    VALUES ('" . $product->getName() . "', '" . $product->getCategory() . "', '" . (string) $product->getPrice() . "')";

        if ($this->connection->query($sqlQuery) === TRUE)
            return true;
        return false;
    }

    public function updateProduct(int $productID, Product $newProduct) : bool {
        $sqlQuery = "UPDATE `" . $this->tableName . "` SET `Name` = '" . $newProduct->getName() . "', `Category` = '" 
                . $newProduct->getCategory() . "', `Price in dollars` = '" . (string) $newProduct->getPrice() . "' WHERE `ID` = '" . (string) $productID . "'";

        if ($this->connection->query($sqlQuery) === TRUE)
            return true;
        return false;
    }

    public function deleteProduct(int $productID) : bool {
        $sqlQuery = "DELETE FROM `" . $this->tableName . "` WHERE `ID` = '" . $productID . "'";

        if ($this->connection->query($sqlQuery) === TRUE)
            return true;
        return false;
    }
}
?>
