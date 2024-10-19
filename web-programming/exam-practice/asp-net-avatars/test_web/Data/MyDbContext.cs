using Microsoft.EntityFrameworkCore;
using test_web.Models;

namespace test_web.Data
{
	public class MyDbContext : DbContext
	{
		public MyDbContext(DbContextOptions options) : base(options)
		{
		}

		public DbSet<User> Users { get; set; }
		public DbSet<Log> Logs { get; set; }
		public DbSet<Avatar> Avatars { get; set; }
	}
}
