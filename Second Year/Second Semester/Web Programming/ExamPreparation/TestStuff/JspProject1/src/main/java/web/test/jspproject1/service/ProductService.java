package web.test.jspproject1.service;

import web.test.jspproject1.model.Product;
import web.test.jspproject1.repository.ProductRepository;

public class ProductService {
    private final ProductRepository productRepository;

    public ProductService() {
        productRepository = new ProductRepository();
    }

    public void save(Product product) {
        productRepository.save(product);
    }

    public void update(Product product) {
        productRepository.update(product);
    }

    public void delete(Integer id) {
        productRepository.delete(id);
    }
}
