using Newtonsoft.Json;

namespace simulation.ViewModel
{
    [JsonObject(MemberSerialization.OptIn)]
    public class Material : Observable
    {
        public Material()
        {
            Name = "";
            L = 0;
            h = 0;
            b = 0;
            ro = 0;
            E = 0;
        }

        [JsonProperty]
        private string _Name;

        public string Name { get { return _Name; } set { _Name = value; RaisePropertyChanged("Name"); } }

        [JsonProperty]
        private double _L;

        public double L { get { return _L; } set { _L = value; RaisePropertyChanged("L"); } }

        [JsonProperty]
        private double _b;

        public double b { get { return _b; } set { _b = value; RaisePropertyChanged("b"); } }

        [JsonProperty]
        private double _h;

        public double h { get { return _h; } set { _h = value; RaisePropertyChanged("h"); } }

        [JsonProperty]
        private double _ro;

        public double ro { get { return _ro; } set { _ro = value; RaisePropertyChanged("ro"); } }

        [JsonProperty]
        private double _E;

        public double E { get { return _E; } set { _E = value; RaisePropertyChanged("E"); } }
    }
}