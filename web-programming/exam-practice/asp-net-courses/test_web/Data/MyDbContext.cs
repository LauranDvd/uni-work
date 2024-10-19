using Microsoft.EntityFrameworkCore;
using test_web.Models;

namespace test_web.Data
{
    public class MyDbContext : DbContext
    {
        public MyDbContext(DbContextOptions options) : base(options)
        {
        }

        public DbSet<Person> Persons { get; set; }
        public DbSet<Course> Courses { get; set; }
    }
}
