package web.test.jspproject1.repository;

import web.test.jspproject1.model.Product;

import java.sql.DriverManager;
import java.sql.SQLException;

public class ProductRepository {
    private static final String databaseUrl = "jdbc:postgresql://localhost:5432/web-test";
    private static final String databaseUsername = "postgres";
    private static final String databasePassword = "postgres";

    public ProductRepository() {
        try {
            Class.forName("org.postgresql.Driver");  // load driver
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    public void save(Product product) {
        String query = "INSERT INTO public.\"Product\"(name, price) VALUES(?, ?) ON CONFLICT(name) DO UPDATE " +
                "SET name = excluded.name, price = excluded.price";
        try(var connection = DriverManager.getConnection(databaseUrl, databaseUsername, databasePassword);
            var statement = connection.prepareStatement(query);
        ) {
            statement.setString(1, product.getName());
            statement.setInt(2, product.getPrice());

            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void update(Product product) {
        String query = "UPDATE public.\"Product\" SET name = ?, price = ? WHERE id = ?;";
        try(var connection = DriverManager.getConnection(databaseUrl, databaseUsername, databasePassword);
            var statement = connection.prepareStatement(query);
        ) {
            statement.setString(1, product.getName());
            statement.setInt(2, product.getPrice());
            statement.setInt(3, product.getId());

            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void delete(Integer id) {
        String query = "DELETE FROM public.\"Product\" WHERE id = ?";
        try(var connection = DriverManager.getConnection(databaseUrl, databaseUsername, databasePassword);
            var statement = connection.prepareStatement(query);
        ) {
            statement.setInt(1, id);
            statement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
