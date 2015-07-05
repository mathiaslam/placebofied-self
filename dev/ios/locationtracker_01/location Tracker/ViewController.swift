import UIKit
import CoreLocation
import MapKit

class ViewController: UIViewController, CLLocationManagerDelegate, MKMapViewDelegate {
    
    @IBOutlet weak var theMap: MKMapView!
    @IBOutlet weak var theLabel: UILabel!
    @IBOutlet weak var startTracking: UIButton!
    @IBOutlet weak var stopTracking: UIButton!
    @IBOutlet weak var clearTrack: UIButton!
    @IBOutlet weak var theTime: UILabel!
    
    
    var polyline:MKPolyline = MKPolyline()
    var manager:CLLocationManager!
    var myLocations: [CLLocation] = []
    var startTime = NSTimeInterval()
    
    
    func updateTime() {
        var currentTime = NSDate.timeIntervalSinceReferenceDate()
        
        //Find the difference between current time and start time.
        var elapsedTime: NSTimeInterval = currentTime; -startTime
        
        //calculate the minutes in elapsed time.
        let minutes = UInt8(elapsedTime / 60.0)
        elapsedTime -= (NSTimeInterval(minutes) * 60)
        
        //calculate the seconds in elapsed time.
        let seconds = UInt8(elapsedTime)
        elapsedTime -= NSTimeInterval(seconds)
        
        //find out the fraction of milliseconds to be displayed.
        let fraction = UInt8(elapsedTime * 100)
        
        //add the leading zero for minutes, seconds and millseconds and store them as string constants
        //let strMinutes = minutes > 9 ? String(minutes): 0 + String(minutes)
        //let strSeconds = seconds > 9 ? String(seconds): 0 + String(seconds)
        //let strFraction = fraction > 9 ? String(fraction): 0 + String(fraction)
        
        //concatenate minuets, seconds and milliseconds as assign it to the UILabel
        //displayTimeLabel.text = \(strMinutes):\(strSeconds):\(strFraction)
    }
    
    func clearTrack(sender: UIButton){
        theMap.removeOverlays(theMap.overlays)
    }
    
    func stopTracking(sender: UIButton) {
        manager.stopUpdatingLocation()
        myLocations = []
        theLabel.text = "KMH: 0"
        let currentDate = NSDate()
        println("Stop making a line")
    }
    
    func startTracking(sender: UIButton) {
        manager.startUpdatingLocation()
        myLocations = []
        println("Making a line")
    }
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        //Setup our Location Manager
        manager = CLLocationManager()
        manager.delegate = self
        manager.desiredAccuracy = kCLLocationAccuracyBest
        manager.requestAlwaysAuthorization()
        manager.startUpdatingLocation()
       
        
        
        //Setup our Map View
        theMap.delegate = self
        theMap.mapType = MKMapType.Hybrid
        theMap.showsUserLocation = true
        
        
    }
    
    
    func locationManager(manager:CLLocationManager, didUpdateLocations locations:[AnyObject]) {
        

        
        // type of ms is automatically inferred to be CLLocationSpeed (alias for Double)
        let ms =  manager.location.speed    // 3.6 floating-point literal is automatically converted to appropriate type
        // type and kph is automatically a Double
        let kph = ms * 3.6
        
        // theLabel.text = "hello \(locations[0]) Stop \(kph)"
        
        theLabel.text = "KMH: \(kph)"
        myLocations.append(locations[0] as! CLLocation)
        
        let spanX = 0.002
        let spanY = 0.002
        var newRegion = MKCoordinateRegion(center: theMap.userLocation.coordinate, span: MKCoordinateSpanMake(spanX, spanY))
        theMap.setRegion(newRegion, animated: true)
        
        if (myLocations.count > 1){
            var sourceIndex = myLocations.count - 1
            var destinationIndex = myLocations.count - 2
            
            let c1 = myLocations[sourceIndex].coordinate
            let c2 = myLocations[destinationIndex].coordinate
            var a = [c1, c2]
            var polyline = MKPolyline(coordinates: &a, count: a.count)
            theMap.addOverlay(polyline)
            
            
            
        }
    }
    
    func mapView(mapView: MKMapView!, rendererForOverlay overlay: MKOverlay!) -> MKOverlayRenderer! {
        
        if overlay is MKPolyline {
            var polylineRenderer = MKPolylineRenderer(overlay: overlay)
            polylineRenderer.strokeColor = UIColor.yellowColor()
            polylineRenderer.lineWidth = 3
            return polylineRenderer
        }
        return nil
    }
}