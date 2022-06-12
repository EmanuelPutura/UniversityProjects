using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Assignment9_ASP.NET.Models
{
    public class Product
    {
        private long id;
        private string name;
        private string category;
        private int price;
        
        public Product(long id, string name, string category, int price)
        {
            this.id = id;
            this.name = name;
            this.category = category;
            this.price = price;
        }

        public long Id
        {
            get { return id; }
            set { id = value; }
        }

        public string Name
        {
            get { return name; }
            set { name = value; }
        }

        public string Category
        {
            get { return category; }
            set { category = value; }
        }

        public int Price
        {
            get { return price; }
            set { price = value; }
        }
    }
}