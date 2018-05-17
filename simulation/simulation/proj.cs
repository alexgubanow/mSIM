using Newtonsoft.Json;

namespace simulation
{
    [JsonObject(MemberSerialization.OptIn)]
    public class proj : Observable
    {
        public proj()
        {
            Name = "";
            l = new Load();
        }

        private string _Name;
        [JsonProperty]
        public string Name { get => _Name; set { _Name = value; RaisePropertyChanged("Name"); } }

        private string _IntegrSchem;
        [JsonProperty]
        public string IntegrSchem { get => _IntegrSchem; set { _IntegrSchem = value; RaisePropertyChanged("IntegrSchem"); } }

        private string _Model;
        [JsonProperty]
        public string Model { get => _Model; set { _Model = value; RaisePropertyChanged("Model"); } }

        private int _elems;
        [JsonProperty]
        public int elems { get => _elems; set { _elems = value; RaisePropertyChanged("elems"); } }

        private double _dT;
        [JsonProperty]
        public double dT { get => _dT; set { _dT = value; RaisePropertyChanged("dT"); } }

        private int _counts;
        [JsonProperty]
        public int counts { get => _counts; set { _counts = value; RaisePropertyChanged("counts"); } }

        private Material _Mater;
        [JsonProperty]
        public Material Mater { get => _Mater; set { _Mater = value; RaisePropertyChanged("Mater"); } }

        private Load _l;
        [JsonProperty]
        public Load l { get => _l; set { _l = value; RaisePropertyChanged("l"); } }
    }
    
}