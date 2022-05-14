<?php
require_once "../model/product.php";

class Repository {
    private $hostname = "localhost:3307";  // TODO: change port if necessary
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

    public function selectAllProducts(int $pageSize, int $currentPage) {
        $limit = $pageSize;
        $offset = $pageSize * $currentPage;
        $sqlQuery = "SELECT * FROM `" . $this->tableName . "` LIMIT " . (string) $limit . " OFFSET " . (string) $offset;

        if ($currentPage < 0) {
            return $this->selectAllProducts($pageSize, 0);
        }

        $result = $this->connection->query($sqlQuery);
        if (!$result)
            return;
        $answerArray = array();

        if ($result->num_rows > 0) {
            // output data from each row
            while($row = $result->fetch_assoc()) {
                $product = new Product((int) $row["ID"], $row["Name"], $row["Category"], (int) $row["Price in dollars"]);
                array_push($answerArray, json_encode($product));
            }
        }
        else {
            return $this->selectAllProducts($pageSize, 0);
        }
        
        array_push($answerArray, $currentPage);
        return json_encode($answerArray);
    }

    public function selectProductsFromCategory(string $category, int $pageSize, int $currentPage) {
        $limit = $pageSize;
        $offset = $pageSize * $currentPage;
        $sqlQuery = "SELECT * FROM `" . $this->tableName . "` WHERE `Category` = '" . $category . "' LIMIT " . (string) $limit . " OFFSET " . (string) $offset;
    
        if ($currentPage < 0) {
            return $this->selectProductsFromCategory($category, $pageSize, 0);
        }

        $result = $this->connection->query($sqlQuery);
        if (!$result) {
            return;
        }
        $answerArray = array();
        
        if ($result->num_rows > 0) {
            // output data from each row
            while($row = $result->fetch_assoc()) {
                $product = new Product((int) $row["ID"], $row["Name"], $row["Category"], (int) $row["Price in dollars"]);
                array_push($answerArray, json_encode($product));
            }
        }
        else if ($currentPage != 0) {
            return $this->selectProductsFromCategory($category, $pageSize, 0);
        }
        
        array_push($answerArray, $currentPage);
        return json_encode($answerArray);
    }

    public function insertProduct(Product $product) : bool {
        // $sqlQuery = "INSERT INTO `" . $this->tableName . "` (`Name`, `Category`, `Price in dollars`) 
        //             VALUES ('" . $product->getName() . "', '" . $product->getCategory() . "', '" . (string) $product->getPrice() . "')";
        //
        // if ($this->connection->query($sqlQuery) === TRUE)
        //     return true;
        // return false;

        $sqlQuery = "INSERT INTO `" . $this->tableName . "` (`Name`, `Category`, `Price in dollars`) VALUES (?, ?, ?)";

        $statement = $this->connection->prepare($sqlQuery);

        $productName = $product->getName();
        $productCategory = $product->getCategory();
        $productPrice = $product->getPrice();

        $statement->bind_param("ssi", $productName, $productCategory, $productPrice);
        $statement->execute();

        return true;
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

    public function checkProductID(int $id) : string {
        $sqlQuery = "SELECT * FROM `" . $this->tableName . "` WHERE `ID` = " . (string) $id;
        $result = $this->connection->query($sqlQuery);

        if ($result->num_rows > 0)
            return json_encode(["valid"]);
        return json_encode(["invalid"]);
    }
}
?>
