<?php
require_once "../service/service.php";

class View {
    private $service;

    public function __construct() {
        $this->service = new Service();
    }

    public function selectProducts(string $category, int $pageSize, int $currentPage) {
        echo $this->service->selectProducts($category, $pageSize, $currentPage);
    }

    public function insertProduct(string $name, string $category, int $price) {
        $this->service->insertProduct($name, $category, $price);
    }

    public function updateProduct(int $id, string $name, string $category, int $price) {
        $this->service->updateProduct($id, $name, $category, $price);
    }

    public function deleteProduct(int $id) {
        $this->service->deleteProduct($id);
    }

    public function checkProductID(int $id) {
        echo $this->service->checkProductID($id);
    }
}
?>
