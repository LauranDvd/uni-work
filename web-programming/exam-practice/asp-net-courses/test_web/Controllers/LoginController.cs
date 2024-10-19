using Microsoft.AspNetCore.Mvc;
using test_web.Data;
using test_web.Models;

namespace test_web.Controllers
{
    public class LoginController : Controller
    {
        private readonly MyDbContext _context;

        public LoginController(MyDbContext context)
        {
            _context = context;
        }

        public IActionResult Index()
        {
            HttpContext.Session.Remove("username");
            HttpContext.Session.Remove("user_id");

            return View();
        }

        public IActionResult InvalidName()
        {
            return View();
        }

        [HttpPost]
        public IActionResult DoLogin(string username)
        {
            Person professor = _context.Persons.FirstOrDefault(
                person => person.Name == username && person.Role == "professor"
                );

            if (professor == null)
            {
                return RedirectToAction("InvalidName", "Login");
            }

            HttpContext.Session.SetString("username", professor.Name);
            HttpContext.Session.SetInt32("user_id", professor.Id);

            return RedirectToAction("Index", "Main");
        }
    }
}
