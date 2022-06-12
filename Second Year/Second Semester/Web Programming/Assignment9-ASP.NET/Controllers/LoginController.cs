﻿using Assignment9_ASP.NET.Persistence;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Assignment9_ASP.NET.Controllers
{
    public class LoginController : Controller
    {
        private DataPersistence dataPersistence = new DataPersistence();

        public ActionResult Index()
        {
            return View("LoginView");
        }

        public ActionResult Login(string username, string password)
        {
            if (dataPersistence.GetAllUsers().Where(user => user.Username.Equals(username) && user.Password.Equals(password)).Count() == 0)
            {
                ViewData["Errors"] = "Invalid password or username!";
                return View("LoginView");
            }

            Session["username"] = username;
            return Redirect("/Products");
        }
    }
}
