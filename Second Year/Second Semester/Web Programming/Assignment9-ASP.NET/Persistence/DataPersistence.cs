using Assignment9_ASP.NET.Models;
using MySql.Data.MySqlClient;
using Npgsql;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Assignment9_ASP.NET.Persistence
{
    public class DataPersistence
    {
        private static string host = "localhost";
        private static string username = "postgres";
        private static string password = "postgres";
        private static string database = "ECommerceStore";
        private string connectionString = $"Host={host};Username={username};Password={password};Database={database};";

        public List<User> GetAllUsers()
        {
            var conn = new NpgsqlConnection(connectionString);
            conn.Open();
            var sql = "SELECT * FROM public.\"Users\"";

            List<User> users = new List<User>();
            var cmd = new NpgsqlCommand(sql, conn);

            NpgsqlDataReader npgsqlDataReader = cmd.ExecuteReader();
            while (npgsqlDataReader.Read())
            {
                users.Add(new User(npgsqlDataReader.GetString(0), npgsqlDataReader.GetString(1)));
            }

            return users;
        }

        public List<Product> GetAllProducts()
        {
            var conn = new NpgsqlConnection(connectionString);
            conn.Open();

            var sql = $"SELECT * FROM public.\"Products\"";

            List<Product> products = new List<Product>();
            var cmd = new NpgsqlCommand(sql, conn);

            NpgsqlDataReader npgsqlDataReader = cmd.ExecuteReader();
            while (npgsqlDataReader.Read())
            {
                products.Add(new Product(npgsqlDataReader.GetInt32(0), npgsqlDataReader.GetString(1), npgsqlDataReader.GetString(2), npgsqlDataReader.GetInt32(3)));
            }

            return products;
        }

        public Tuple<int, List<Product>> GetAllProducts(string category, int pageNumber)
        {
            if (pageNumber < 0)
            {
                return new Tuple<int, List<Product>>(0, GetAllProducts(category, 0).Item2);
            }

            var conn = new NpgsqlConnection(connectionString);
            conn.Open();

            var limit = 4;
            var offset = limit * pageNumber;
            
            var sql = $"SELECT * FROM public.\"Products\" ";
            if (category.ToLower() != "all" && category != "")
            {
                sql += $"WHERE category = '{category}' ";
            }

            sql += $"LIMIT {limit} OFFSET {offset};";

            List<Product> products = new List<Product>();
            var cmd = new NpgsqlCommand(sql, conn);

            NpgsqlDataReader npgsqlDataReader = cmd.ExecuteReader();
            while (npgsqlDataReader.Read())
            {
                products.Add(new Product(npgsqlDataReader.GetInt32(0), npgsqlDataReader.GetString(1), npgsqlDataReader.GetString(2), npgsqlDataReader.GetInt32(3)));
            }

            if (products.Count == 0 && pageNumber != 0)
            {
                return new Tuple<int, List<Product>>(0, GetAllProducts(category, 0).Item2);
            }
            return new Tuple<int, List<Product>>(pageNumber, products);
        }

        public bool CheckProductId(int id)
        {
            var conn = new NpgsqlConnection(connectionString);
            conn.Open();

            var sql = $"SELECT * FROM public.\"Products\" WHERE id = '{id}' ";

            var cmd = new NpgsqlCommand(sql, conn);
            NpgsqlDataReader npgsqlDataReader = cmd.ExecuteReader();

            return npgsqlDataReader.HasRows;
        }

        public void SaveProduct(Product product)
        {
            try
            {
                var conn = new NpgsqlConnection(connectionString);
                conn.Open();

                var sql = $"INSERT INTO public.\"Products\"(name, category, price) VALUES ('{product.Name}', '{product.Category}', {product.Price});";
                var cmd = new NpgsqlCommand(sql, conn);
                cmd.ExecuteNonQuery();
            }
            catch (Npgsql.NpgsqlException ex)
            {
                Console.Write(ex.Message);
            }
        }

        public void UpdateProduct(Product product)
        {
            try
            {
                var conn = new NpgsqlConnection(connectionString);
                conn.Open();

                var sql = $"UPDATE public.\"Products\" SET name = '{product.Name}', category = '{product.Category}', price = {product.Price} WHERE id = {product.Id};";
                var cmd = new NpgsqlCommand(sql, conn);
                cmd.ExecuteNonQuery();
            }
            catch (Npgsql.NpgsqlException ex)
            {
                Console.Write(ex.Message);
            }
        }

        public void RemoveProduct(int productId)
        {
            try
            {
                var conn = new NpgsqlConnection(connectionString);
                conn.Open();

                var sql = $"DELETE FROM public.\"Products\" WHERE id = {productId};";
                var cmd = new NpgsqlCommand(sql, conn);
                cmd.ExecuteNonQuery();
            }
            catch (Npgsql.NpgsqlException ex)
            {
                Console.Write(ex.Message);
            }
        }

        public Product GetProductBasedOnAllFieldsButForId(Product product)
        {
            var conn = new NpgsqlConnection(connectionString);
            conn.Open();

            var sql = $"SELECT * FROM public.\"Products\" WHERE name = '{product.Name}' AND category = '{product.Category}' AND price = {product.Price}";

            List<Product> products = new List<Product>();
            var cmd = new NpgsqlCommand(sql, conn);

            NpgsqlDataReader npgsqlDataReader = cmd.ExecuteReader();
            while (npgsqlDataReader.Read())
            {
                products.Add(new Product(npgsqlDataReader.GetInt32(0), npgsqlDataReader.GetString(1), npgsqlDataReader.GetString(2), npgsqlDataReader.GetInt32(3)));
            }

            return products.Count != 1 ? null : products[0];
        }
    }
}
