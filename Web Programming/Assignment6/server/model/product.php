<?php
class Product implements JsonSerializable {
    private $id;
    private $name;
    private $category;
    private $price;

    public function __construct(int $id, string $name, string $category, int $price) {
        $this->id = $id;
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

    public function jsonSerialize() {
        return [
            'id' => $this->id,
            'name' => $this->name,
            'category' => $this->category,
            'price' => $this->price,
        ];
    }
}
?>
