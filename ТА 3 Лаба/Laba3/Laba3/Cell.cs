using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba3
{
    public class Cell
    {
        public int Row { get; set; }
        public int Column { get; set; }
        public bool Marked { get; set; }
        public bool Wall { get; set; }
        public bool Start { get; set; }
        public bool End { get; set; }
    }
}
