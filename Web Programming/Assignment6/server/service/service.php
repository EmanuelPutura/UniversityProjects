<?php
require_once "../repository/repository.php";
require_once "../model/product.php";

class Service {
    private $repository;

    public function __construct() {
        $this->repository = new Repository();
    }

    public function insertProduct(string $name, string $category, int $price) {
        $product = new Product($name, $category, $price);
        $this->repository->insertProduct($product);
    }

    public function updateProduct(int $id, string $name, string $category, int $price) {
        $product = new Product($name, $category, $price);
        $this->repository->updateProduct($id, $product);
    }

    public function deleteProduct(int $id) {
        $this->repository->deleteProduct($id);
    }
}
?>
