using calcLib;
using Newtonsoft.Json;

namespace simulation
{
    [JsonObject(MemberSerialization.OptIn)]
    public class LoadedElems : Observable
    {
        private string _Name;

        private LoadedElem[] _elems;

        public LoadedElems()
        {
            Name = "";
            elems = new LoadedElem[1] { new LoadedElem() { Id = 0, dT = 1E-6, lDirect = loadDirect.x, lArr = new double[1], lType = loadType.displ } };
        }

        [JsonProperty]
        public string Name { get { return _Name; } set { _Name = value; RaisePropertyChanged("Name"); } }

        [JsonProperty]
        public LoadedElem[] elems { get { return _elems; } set { _elems = value; RaisePropertyChanged("elems"); } }
    }

    [JsonObject(MemberSerialization.OptIn)]
    public class LoadedElem : Observable
    {
        public LoadedElem()
        {
        }

        private int _Id;

        [JsonProperty]
        public int Id { get { return _Id; } set { _Id = value; RaisePropertyChanged("Id"); } }

        private double _dT;

        [JsonProperty]
        public double dT { get { return _dT; } set { _dT = value; RaisePropertyChanged("dT"); } }

        private loadType _lType;

        [JsonProperty]
        public loadType lType { get { return _lType; } set { _lType = value; RaisePropertyChanged("lType"); } }

        private loadDirect _lDirect;

        [JsonProperty]
        public loadDirect lDirect { get { return _lDirect; } set { _lDirect = value; RaisePropertyChanged("lDirect"); } }

        private double[] _lArr;

        [JsonProperty]
        public double[] lArr { get { return _lArr; } set { _lArr = value; RaisePropertyChanged("lArr"); } }
    }
}