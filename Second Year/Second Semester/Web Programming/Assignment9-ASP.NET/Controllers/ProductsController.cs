using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Assignment9_ASP.NET.Controllers
{
    public class ProductsController : Controller
    {
        public ActionResult Index()
        {
            return Products();
        }

        public ActionResult Products()
        {
            return View("ProductsHomeView");
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
    }
}
