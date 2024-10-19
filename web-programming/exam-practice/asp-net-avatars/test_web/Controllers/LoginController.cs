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

		public IActionResult InvalidCredentials()
		{
			return View();
		}

		[HttpPost]
		public IActionResult DoLogin(string username, string password)
		{
			User user = _context.Users.FirstOrDefault(
				person => person.Username == username && person.Password == password
			);

			if (user == null)
			{
				return RedirectToAction("InvalidCredentials", "Login");
			}

			HttpContext.Session.SetString("username", user.Username);
			HttpContext.Session.SetInt32("user_id", user.Id);

			return RedirectToAction("Index", "Main");
		}
	}
}
