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
            if (Session["username"] == null)
            {
                return RedirectToAction("Index", "Login/");
            }

            return Products();
        }

        public string Products(string category, int currentPage)
        {
            if (Session["username"] == null)
            {
                return "Invalid Session!";
            }

            var result = dataPersistence.GetAllProducts(category, currentPage);
            return JsonConvert.SerializeObject(new Tuple<int, string>(result.Item1, BuildTableFromProducts(result.Item2)));
        }

        public bool CheckProductId(int id)
        {
            return dataPersistence.CheckProductId(id);
        }

        public ActionResult InsertProduct()
        {
            if (Session["username"] == null)
            {
                return RedirectToAction("Index", "Login/");
            }

            return View("ProductsInsertView");
        }

        public void InsertProductPersist(string productName, string productCategory, string productPrice)
        {
            if (Session["username"] == null)
            {
                return;
            }

            int intProductPrice;
            if (!int.TryParse(productPrice, out intProductPrice))
            {
                return;
            }

            dataPersistence.SaveProduct(new Product(-1, productName, productCategory, intProductPrice));
        }

        public ActionResult UpdateProduct()
        {
            if (Session["username"] == null)
            {
                return RedirectToAction("Index", "Login/");
            }

            ViewData["Products"] = dataPersistence.GetAllProducts();
            return View("ProductsUpdateView");
        }

        public ActionResult UpdateProductPersist(string id, string name, string category, string price)
        {
            if (Session["username"] == null)
            {
                return RedirectToAction("Index", "Login/");
            }

            int intProductId, intProductPrice;
            if (!int.TryParse(price, out intProductPrice) || !int.TryParse(id, out intProductId))
            {
                return null;
            }

            dataPersistence.UpdateProduct(new Product(intProductId, name, category, intProductPrice));
            return UpdateProduct();
        }

        public ActionResult DeleteProduct()
        {
            if (Session["username"] == null)
            {
                return RedirectToAction("Index", "Login/");
            }

            ViewData["Products"] = dataPersistence.GetAllProducts();
            return View("ProductsDeleteView");
        }

        public void DeleteProductPersist(string name, string category, string price)
        {
            if (Session["username"] == null)
            {
                return;
            }

            int intProductPrice;
            if (!int.TryParse(price, out intProductPrice))
            {
                return;
            }

            var product = dataPersistence.GetProductBasedOnAllFieldsButForId(new Product(-1, name, category, intProductPrice));
            dataPersistence.RemoveProduct((int)product.Id);
        }

        public ActionResult ProductDetailsPrepare(string name, string category, string price)
        {
            if (Session["username"] == null)
            {
                return RedirectToAction("Index", "Login/");
            }

            int intProductPrice;
            if (!int.TryParse(price, out intProductPrice))
            {
                return null;
            }

            var product = dataPersistence.GetProductBasedOnAllFieldsButForId(new Product(-1, name, category, intProductPrice));
            // Session["Product"] = product;

            ViewData["Product"] = product;
            return View("ProductDetailsView");

        }

        private ActionResult Products()
        {
            if (Session["username"] == null)
            {
                return RedirectToAction("Index", "Login/");
            }

            return View("ProductsHomeView");
        }

        private string BuildTableFromProducts(List<Product> products)
        {
            if (Session["username"] == null)
            {
                return "Invalid Session!";
            }

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
