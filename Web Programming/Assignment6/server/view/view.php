<?php
require_once "../service/service.php";

class View {
    private $service;

    public function __construct() {
        $this->service = new Service();
    }

    public function insertProduct(string $name, string $category, string $price) {
        $this->service->insertProduct($name, $category, $price);
    }
}
?>
