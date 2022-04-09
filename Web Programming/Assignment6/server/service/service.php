<?php
require_once "../repository/repository.php";
require_once "../model/product.php";

class Service {
    private $repository;

    public function __construct() {
        $this->repository = new Repository();
    }

    public function insertProduct(string $name, string $category, string $price) {
        $product = new Product($name, $category, (int) $price);
        $this->repository->insertProduct($product);
    }
}
?>
