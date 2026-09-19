class Solution(object):
    def checkOverlap(self, radius, xCenter, yCenter, x1, y1, x2, y2):
        
        # Find closest x-coordinate
        x = max(x1, min(xCenter, x2))
        
        # Find closest y-coordinate
        y = max(y1, min(yCenter, y2))
        
        # Calculate squared distance
        distance = (x - xCenter) ** 2 + (y - yCenter) ** 2
        
        # Check if point is inside or on circle
        return distance <= radius ** 2