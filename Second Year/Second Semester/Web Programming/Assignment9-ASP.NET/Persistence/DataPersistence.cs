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
    }
}
