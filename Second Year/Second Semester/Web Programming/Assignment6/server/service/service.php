<?php
require_once "../repository/repository.php";
require_once "../model/product.php";

class Service {
    private $repository;

    public function __construct() {
        $this->repository = new Repository();
    }

    public function selectProducts(string $category, int $pageSize, int $currentPage) {
        if ($category === "all")
            return $this->repository->selectAllProducts($pageSize, $currentPage);
        return $this->repository->selectProductsFromCategory($category, $pageSize, $currentPage);
    }

    public function insertProduct(string $name, string $category, int $price) {
        $product = new Product(0, $name, $category, $price);
        $this->repository->insertProduct($product);
    }

    public function updateProduct(int $id, string $name, string $category, int $price) {
        $product = new Product(0, $name, $category, $price);
        $this->repository->updateProduct($id, $product);
    }

    public function deleteProduct(int $id) {
        $this->repository->deleteProduct($id);
    }

    public function checkProductID(int $id) : string {
        return $this->repository->checkProductID($id);
    }
}
?>
