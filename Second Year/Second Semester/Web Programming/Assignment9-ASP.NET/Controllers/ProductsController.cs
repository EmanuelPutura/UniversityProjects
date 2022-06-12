using Assignment9_ASP.NET.Models;
using Assignment9_ASP.NET.Persistence;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Assignment9_ASP.NET.Controllers
{
    public class ProductsController : Controller
    {
        private DataPersistence dataPersistence = new DataPersistence();

        public ActionResult Index()
        {
            return Products();
        }

        public string Products(string category, int currentPage)
        {
            var result = dataPersistence.GetAllProducts(category, currentPage);
            return JsonConvert.SerializeObject(new Tuple<int, string>(result.Item1, BuildTableFromProducts(result.Item2)));
        }

        public ActionResult InsertProduct()
        {
            return View("ProductsInsertView");
        }

        public ActionResult UpdateProduct()
        {
            return View("ProductsUpdateView");
        }

        public ActionResult DeleteProduct()
        {
            return View("ProductsDeleteView");
        }

        private ActionResult Products()
        {
            return View("ProductsHomeView");
        }

        private string BuildTableFromProducts(List<Product> products)
        {
            var resultTable = "<table id=\"products-table\"><tr>";
            resultTable += "<th>Product ID</th>";
            resultTable += "<th>Product Name</th>";
            resultTable += "<th>Product Category</th>";
            resultTable += "<th>Product Price</th></tr>";

            for (int i = 0; i < 4; ++i)
            {
                var productId = products.Count > i ? products[i].Id.ToString() : "";
                var productName = products.Count > i ? products[i].Name : "";
                var productCategory = products.Count > i ? products[i].Category : "";
                var productPrice = products.Count > i ? products[i].Price.ToString() : "";

                resultTable += $"<tr><td>{productId}</td><td>{productName}</td><td>{productCategory}</td><td>{productPrice}</td></tr>";
            }

            return resultTable;
        }
    }
}
