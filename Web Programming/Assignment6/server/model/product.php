<?php
class Product {
    private $name;
    private $category;
    private $price;

    public function __construct(string $name, string $category, int $price) {
        $this->name = $name;
        $this->category = $category;
        $this->price = $price;
    }

    public function getName() : string {
        return $this->name;
    }

    public function getCategory() : string {
        return $this->category;
    }

    public function getPrice() : int {
        return $this->price;
    }
}
?>
